// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GASPlayerCharacter.generated.h"


UCLASS(config=Game)
class UNREALGAS_API AGASPlayerCharacter : public AGASCharacterBase
{
	GENERATED_BODY()

public:
	AGASPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "GAS|Camera")
	float GetStartingCameraBoomArmLength() const { return StartingCameraBoomArmLength; };

	UFUNCTION(BlueprintCallable, Category = "GAS|Camera")
	FVector GetStartingCameraBoomLocation() const { return StartingCameraBoomLocation; };

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Camera")
	FVector StartingCameraBoomLocation;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Input")
	class UInputConfig* InputConfig;

	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

	// For GAS
	bool ASCInputBound = false;
	
	void InitializeGas(class AGASPlayerState* PS);
	
	void BindAscInput();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
};

