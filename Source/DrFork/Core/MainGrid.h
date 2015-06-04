// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MainGrid.generated.h"

UCLASS()
class DRFORK_API AMainGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	AMainGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
