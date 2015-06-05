// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DrFork.h"
#include "DrForkGameMode.h"
#include "DrForkPlayerController.h"

ADrForkGameMode::ADrForkGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = NULL;
	PlayerControllerClass = ADrForkPlayerController::StaticClass();
}
