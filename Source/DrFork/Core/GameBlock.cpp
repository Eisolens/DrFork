#include "DrFork.h"
#include "GameBlock.h"

AGameBlock::AGameBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IsCanMove = false;
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->AttachTo(DummyRoot);
	Link = nullptr;
}

void AGameBlock::Init(BlockType Type, BlockColor Color, UStaticMesh* Mesh, UMaterialInstance* Material)
{
	Types.Color = Color;
	Types.Type = Type;

	switch (Type)
	{
	case BlockType::Tablet :
		PrimaryActorTick.bCanEverTick = true;
		this->SetActorScale3D(FVector(1, 0.5f, 1));
		this->RootComponent->SetMobility(EComponentMobility::Movable);
		break;
	case BlockType::Virus:
		PrimaryActorTick.bCanEverTick = false;
		this->SetActorScale3D(FVector(1, 1, 0.5f));
		this->RootComponent->SetMobility(EComponentMobility::Stationary);
		break;
	}

	BlockMesh->SetStaticMesh(Mesh);
	BlockMesh->SetMaterial(0, Material);
	//BlockMesh->OnClicked.AddDynamic(this, &ADrForkBlock::BlockClicked);
	//BlockMesh->OnInputTouchBegin.AddDynamic(this, &ADrForkBlock::OnFingerPressedBlock);
}

void AGameBlock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

