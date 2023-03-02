// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PlayerAIController.h"

APlayerAIController::APlayerAIController()
{
	// If we create a new AI instance, it'll want to have it's own player state
	bWantsPlayerState = true;
}
