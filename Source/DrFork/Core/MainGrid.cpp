// Fill out your copyright notice in the Description page of Project Settings.

#include "DrFork.h"
#include "MainGrid.h"


// Sets default values
AMainGrid::AMainGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

