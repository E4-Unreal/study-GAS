// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGASGameMode.h"
#include "UnrealGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealGASGameMode::AUnrealGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
