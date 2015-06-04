// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DrFork.h"
#include "DrForkGameMode.h"
#include "DrForkPlayerController.h"

ADrForkGameMode::ADrForkGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = ADrForkPlayerController::StaticClass();
}
