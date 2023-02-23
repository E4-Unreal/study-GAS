# UnrealGAS
Unreal Engine 5.1 Gameplay Ability System (GAS) Tutorial

## 참고 링크
- Youtube 영상
  - [[UE5] General Gameplay Ability System Tutorial](https://www.youtube.com/watch?v=LxT8Fc2ejgI&list=PLuS6-Pdt2hhYGZkME7K7ZDT2qf4vbY5c3)
- GASDocumentation
  - 3\. [Setting Up a Project Using GAS](https://github.com/tranek/GASDocumentation#setup)
  - 4.4.3 [Defining Attributes](https://github.com/tranek/GASDocumentation#concepts-as-attributes)
  - 4.3.3 [Meta Attributes](https://github.com/tranek/GASDocumentation#concepts-a-meta)

## 프로젝트 설정
1. 에디터에서 GameplayAbilitySystem 플러그인 활성화 (편집 > 플러그인 > Gameplay > Gameplay Abilities)
2. `*.Build.cs`의 `PrivateDependencyModuleNames`에 `"GameplayAbilities", "GameplayTags", "GameplayTasks"` 모듈 추가
3. 비쥬얼 스튜디오 프로젝트 파일을 새로 고치거나 재생성
4. `UAssetManager`를 상속받은 커스텀 애셋 매니저 생성

<details>
<summary>소스 코드 보기</summary>
<div markdown="1">

*.Build.cs
```cpp
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealGAS : ModuleRules
{
	public UnrealGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Default Modules
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		
		// Additional Modules for GAS
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
	}
	
}
```

GASAssetManager.h
```cpp
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAS_API UGASAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
};
```

GASAssetManager.cpp
```cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "GASAssetManager.h"
#include "AbilitySystemGlobals.h"

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}

```

DefaultEngine.ini
```cpp
[/Script/Engine.Engine]
+ActiveGameNameRedirects=(OldGameName="TP_ThirdPerson",NewGameName="/Script/UnrealGAS")
+ActiveGameNameRedirects=(OldGameName="/Script/TP_ThirdPerson",NewGameName="/Script/UnrealGAS")
+ActiveClassRedirects=(OldClassName="TP_ThirdPersonGameMode",NewClassName="UnrealGASGameMode")
+ActiveClassRedirects=(OldClassName="TP_ThirdPersonCharacter",NewClassName="UnrealGASCharacter")
AssetManagerClassName=/Script/UnrealGAS.GASAssetManager
```
</div>
</details>

## Attributes 정의
- `Attributes`는 `AttributeSet` 헤더 파일에서 C++로만 정의할 수 있다
- `UAttributeSet`를 상속받은 커스텀 `AttributeSet` 생성

<details>
<summary>소스 코드 보기</summary>
<div markdown="2">

CharacterAttributeSetBase.h
```cpp
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UNREALGAS_API UCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MaxMana)

	// Damage is meta attribute used by the DamageExecution on calculate final damage, which then turns...
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Damage)

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldHealth);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

```
CharacterAttributeSetBase.cpp
```cpp
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Net/UnrealNetwork.h"

void UCharacterAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, Health, OldHealth);
}

void UCharacterAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, MaxHealth, OldHealth);
}

void UCharacterAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, Mana, OldHealth);
}

void UCharacterAttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, MaxMana, OldHealth);
}

void UCharacterAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, MaxMana, COND_None, REPNOTIFY_Always);
}

```

</div>
</details>