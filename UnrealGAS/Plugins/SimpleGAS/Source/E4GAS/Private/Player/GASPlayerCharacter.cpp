// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/GASPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AI/PlayerAIController.h"

// For Input
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/GASEnhancedInputComponent.h"
#include "GASGameplayTags.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Player/GASPlayerState.h"


//////////////////////////////////////////////////////////////////////////
// AGASPlayerCharacter

AGASPlayerCharacter::AGASPlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AIControllerClass = APlayerAIController::StaticClass();
}

void AGASPlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGASPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	UGASInputComponent* GASEnhancedInputComponent = CastChecked<UGASInputComponent>(PlayerInputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(GASEnhancedInputComponent);

	const FGASGameplayTags& GameplayTags = FGASGameplayTags::Get();
	
	//Bind Input actions by tag
	GASEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	GASEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	GASEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

	//Bind Input actions by ASC
	BindASCInput();

	// Todo 테스트 중. 함수로 만들 예정
}

void AGASPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	// With GAS
	if(!IsAlive()){ return; }
	
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGASPlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	// With GAS
	if(!IsAlive()){ return; }
		
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGASPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	// With GAS
	if(!IsAlive()){ return; }
	
	Jump();
}

void AGASPlayerCharacter::InitializeGas(AGASPlayerState* PS)
{
	// Inherited From AGASCharacterBase
	AttributeSetBase = PS->GetAttributeSetBase();
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		
	// PlayerController에서 이미 설정하였지만, AI PlayerController에서 설정을 안 해줄 수 있으므로 캐릭터 자체에서도 설정을 하도록 함
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	// GE_PlayerAttributes
	InitializeAttributes();
	
	// Default Settings for GAS
	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
}

void AGASPlayerCharacter::BindASCInput()
{
	if(!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/E4GAS"), FName("EGASAbilityID"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(
			InputComponent,
			FGameplayAbilityInputBinds(
				FString("ConfirmTarget"),
				FString("CancelTarget"),
				AbilityEnumAssetPath,
				static_cast<int32>(EGASAbilityID::Confirm),
				static_cast<int32>(EGASAbilityID::Cancel)));
		ASCInputBound = true;
	}
}

void AGASPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();

	if(PS)
	{
		InitializeGas(PS);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void AGASPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();

	if(PS)
	{
		InitializeGas(PS);
		BindASCInput();
	}
}




