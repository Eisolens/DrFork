// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DrFork.h"
#include "DrForkPlayerController.h"

ADrForkPlayerController::ADrForkPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
