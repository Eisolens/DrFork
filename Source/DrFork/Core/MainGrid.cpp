#include "DrFork.h"
#include "MainGrid.h"
#include "GameBlock.h"
#include "LogicGrid.h"

AMainGrid::AMainGrid(const FObjectInitializer& ObjectInitializer)
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	ControlledBlock = nullptr;

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> tablet(TEXT("/Game/Meshes/Tablet.Tablet"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> redMaterial(TEXT("/Game/Materials/RedMat"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> blueMaterial(TEXT("/Game/Materials/BlueMat"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> yeullouMaterial(TEXT("/Game/Materials/YeullouMat"));

	Tablet = tablet.Get();
	RedMat = redMaterial.Get();
	BlueMat = blueMaterial.Get();
	YeullouMat = yeullouMaterial.Get();
}

void AMainGrid::StartGame()
{
	for (auto chield : this->Children)
		chield->Destroy();

	LogicGrid* logicGrid = LogicGrid::Get();
	logicGrid->NewLevel();

	for (int x = 0; x < logicGrid->GridWidth; x++)
		for (int y = 0; y < logicGrid->GridHeight; y++)
		{
			if (logicGrid->Grid[x][y].Type == BlockType::Virus)
			{
				AGameBlock* NewBlock = GetWorld()->SpawnActor<AGameBlock>(FVector(y * BlockSize, x * BlockSize, 0), FRotator(0, 0, 0));

				UMaterialInstance* bufmat = nullptr;

				switch (logicGrid->Grid[x][y].Color)
				{
				case BlockColor::Blue :
					bufmat = BlueMat;
					break;
				case BlockColor::Red :
					bufmat = RedMat;
					break;
				case BlockColor::Yellou :
					bufmat = YeullouMat;
					break;
				}

				NewBlock->Init(logicGrid->Grid[x][y].Type, logicGrid->Grid[x][y].Color, Tablet, bufmat);
				NewBlock->AttachRootComponentToActor(this);
			}
		}
}

// Called when the game starts or when spawned
void AMainGrid::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

// Called every frame
void AMainGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

