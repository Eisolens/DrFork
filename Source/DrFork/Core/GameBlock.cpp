#include "DrFork.h"
#include "GameBlock.h"

AGameBlock::AGameBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IsCanMove = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AGameBlock::Init(BlockType Type, BlockColor Color)
{
	Types.Color = Color;
	Types.Type = Type;
}

void AGameBlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

