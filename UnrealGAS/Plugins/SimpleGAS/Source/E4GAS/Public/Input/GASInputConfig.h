#pragma once

#include "CoreMinimal.h"
#include "E4GASModule.h"
#include "Engine/DataAsset.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "GASInputConfig.generated.h"

class UInputAction;
struct FGameplayTag;


/**
 * FTaggedInputAction
 *
 *	Struct used to map an input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FTaggedInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 *
 */
UCLASS()
class E4GAS_API UGASInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Returns the first Input Action associated with a given tag.
	UFUNCTION(BlueprintCallable, Category = "GAS|PlayerCharacter")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;

	UFUNCTION(BlueprintCallable, Category = "GAS|PlayerCharacter")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;

public:
	// List of input actions used by the owner. These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTaggedInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTaggedInputAction> AbilityInputActions;
};

/**
 * FTaggedAbilityID
 *
 *	Struct used to map an ability ID to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FTaggedAbilityID
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGASAbilityID AbilityID = EGASAbilityID::None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 *
 */
UCLASS()
class E4GAS_API UAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Returns the first Input Action associated with a given tag.
	EGASAbilityID FindAbilityIDForTag(const FGameplayTag& InputTag) const;

public:
	// List of input actions used by the owner. These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputTag"))
	TArray<FTaggedAbilityID> TaggedAbilityIDs;
};