#include "DrFork.h"
#include "GameBlock.h"
#include "Components/DestructibleComponent.h"

AGameBlock::AGameBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	RotState = TabletRotState::Right;
	PrimaryActorTick.bCanEverTick = false;
	Link = nullptr;
}

//void AGameBlock::Init(BlockType Type, BlockColor Color, UStaticMesh* Mesh, UMaterialInstance* Material)
//{
//	Types.Color = Color;
//	Types.Type = Type;
//
//	switch (Type)
//	{
//	case BlockType::Tablet :
//		this->SetActorScale3D(FVector(1, 0.5f, 1));
//		this->RootComponent->SetMobility(EComponentMobility::Movable);
//		break;
//	case BlockType::Virus:
//		this->SetActorScale3D(FVector(1, 0.5f, 1));
//		this->RootComponent->SetMobility(EComponentMobility::Stationary);
//		break;
//	}
//
//	BlockMesh->SetStaticMesh(Mesh);
//	BlockMesh->SetMaterial(0, Material);
//}

void AGameBlock::Init(BlockType Type, BlockColor Color, UDestructibleMesh* Mesh, UMaterialInstance* Material)
{
	Types.Color = Color;
	Types.Type = Type;

	switch (Type)
	{
	case BlockType::Tablet:
		this->SetActorScale3D(FVector(1, 0.5f, 1));
		this->RootComponent->SetMobility(EComponentMobility::Movable);
		break;
	case BlockType::Virus:
		this->SetActorScale3D(FVector(1, 1, 0.5f));
		this->RootComponent->SetMobility(EComponentMobility::Stationary);
		break;
	}

	GetDestructibleComponent()->SetDestructibleMesh(Mesh);
	GetDestructibleComponent()->SetMaterial(0, Material);
}

void AGameBlock::SetOutline(bool check)
{
	GetDestructibleComponent()->SetRenderCustomDepth(check);
	if(Link)
		Link->GetDestructibleComponent()->SetRenderCustomDepth(check);
}

void AGameBlock::ApplyDamage()
{
	GetDestructibleComponent()->ApplyRadiusDamage(100, GetActorLocation(), 1, 50000, false);
}