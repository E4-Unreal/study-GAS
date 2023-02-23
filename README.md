# UnrealGAS
Unreal Engine 5.1 Gameplay Ability System (GAS) Tutorial

## 프로젝트 설정
1. 에디터에서 GameplayAbilitySystem 플러그인 활성화 (편집 > 플러그인 > Gameplay > Gameplay Abilities)
2. `*.Build.cs`의 `PrivateDependencyModuleNames`에 `"GameplayAbilities", "GameplayTags", "GameplayTasks"` 모듈 추가
3. 비쥬얼 스튜디오 프로젝트 파일을 새로 고치거나 재생성
4. UAssetManager를 상속받은 커스텀 애셋 매니저 생성

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