// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "DrForkPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ADrForkPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADrForkPlayerController(const FObjectInitializer& ObjectInitializer);
};


