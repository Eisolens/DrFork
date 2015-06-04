#pragma once

#include "GameFramework/Actor.h"
#include "Types.h"
#include "GameBlock.generated.h"

UCLASS()
class DRFORK_API AGameBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	BlockTypes Types;

	bool IsCanMove;

	AGameBlock(const FObjectInitializer& ObjectInitializer);

	void Init(BlockType Type, BlockColor Color);

	virtual void Tick( float DeltaSeconds ) override;
};
