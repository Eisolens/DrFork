#include "DrFork.h"
#include "GameBlock.h"

AGameBlock::AGameBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->AttachToComponent(DummyRoot, FAttachmentTransformRules::KeepRelativeTransform);
	RotState = TabletRotState::Right;
	PrimaryActorTick.bCanEverTick = false;
	Link = nullptr;
}

void AGameBlock::Init(BlockType Type, BlockColor Color, UStaticMesh* Mesh, UMaterialInstance* Material)
{
	Types.Color = Color;
	Types.Type = Type;

	switch (Type)
	{
	case BlockType::Tablet :
		this->SetActorScale3D(FVector(1, 0.5f, 1));
		this->RootComponent->SetMobility(EComponentMobility::Movable);
		break;
	case BlockType::Virus:
		this->SetActorScale3D(FVector(2, 2, 1));
		this->RootComponent->SetMobility(EComponentMobility::Stationary);
		break;
	}

	BlockMesh->SetStaticMesh(Mesh);
	BlockMesh->SetMaterial(0, Material);
}

void AGameBlock::SetOutline(bool check)
{
	BlockMesh->SetRenderCustomDepth(check);
	if(Link)
		Link->BlockMesh->SetRenderCustomDepth(check);
}