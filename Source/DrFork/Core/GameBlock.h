#pragma once

//#include "GameFramework/Actor.h"
#include "Classes/PhysicsEngine/DestructibleActor.h"
#include "Engine/DestructibleMesh.h"
#include "Types.h"
#include "GameBlock.generated.h"

UCLASS()
class DRFORK_API AGameBlock : public ADestructibleActor
{
	GENERATED_BODY()

	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class UStaticMeshComponent* BlockMesh;

public:	
	BlockTypes Types;
	TabletRotState RotState;
	AGameBlock* Link;
	Point Pos;

	AGameBlock(const FObjectInitializer& ObjectInitializer);
	//void Init(BlockType Type, BlockColor Color, UStaticMesh* Mesh, UMaterialInstance* Material);
	void Init(BlockType Type, BlockColor Color, UDestructibleMesh* Mesh, UMaterialInstance* Material);
	void SetOutline(bool check);
	void ApplyDamage();
};
