// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "DrForkGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ADrForkGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADrForkGameMode(const FObjectInitializer& ObjectInitializer);
};



