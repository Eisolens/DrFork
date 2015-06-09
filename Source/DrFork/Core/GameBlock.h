#pragma once

#include "GameFramework/Actor.h"
#include "Types.h"
#include "GameBlock.generated.h"

UCLASS()
class DRFORK_API AGameBlock : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:	
	BlockTypes Types;
	AGameBlock* Link;
	Point Pos;
	bool IsCanMove;

	AGameBlock(const FObjectInitializer& ObjectInitializer);
	void Init(BlockType Type, BlockColor Color, UStaticMesh* Mesh, UMaterialInstance* Material);
	virtual void Tick( float DeltaSeconds ) override;
	void SetOutline(bool check);
};
