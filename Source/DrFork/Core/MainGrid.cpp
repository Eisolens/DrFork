#include "DrFork.h"
#include "MainGrid.h"
#include "GameBlock.h"
#include "LogicGrid.h"

AMainGrid::AMainGrid(const FObjectInitializer& ObjectInitializer)
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	ControlledTablet = nullptr;

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> tablet(TEXT("/Game/Meshes/Tablet"));
	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> virus(TEXT("/Game/Meshes/Virus"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> redMaterial(TEXT("/Game/Materials/RedMat"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> blueMaterial(TEXT("/Game/Materials/BlueMat"));
	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> yeullouMaterial(TEXT("/Game/Materials/YeullouMat"));

	Tablet = tablet.Get();
	Virus = virus.Get();
	RedMat = redMaterial.Get();
	BlueMat = blueMaterial.Get();
	YeullouMat = yeullouMaterial.Get();

	PrimaryActorTick.bCanEverTick = true;
	GameState = GameState::Finished;
}

AGameBlock* AMainGrid::CreateBlock(Point pos, FRotator rot)
{
	LogicGrid* logicGrid = LogicGrid::Get();
	AGameBlock* NewBlock = GetWorld()->SpawnActor<AGameBlock>(FVector(pos.Y * BlockSize, pos.X * BlockSize, 0), rot);

	NewBlock->Pos = pos;

	UMaterialInstance* bufmat = nullptr;

	switch (logicGrid->Grid[pos.X][pos.Y].Color)
	{
	case BlockColor::Blue:
		bufmat = BlueMat;
		break;
	case BlockColor::Red:
		bufmat = RedMat;
		break;
	case BlockColor::Yellou:
		bufmat = YeullouMat;
		break;
	}

	UStaticMesh* bufMesh = nullptr;

	switch (logicGrid->Grid[pos.X][pos.Y].Type)
	{
	case BlockType::Virus:
		bufMesh = Virus;
		break;

	case BlockType::Tablet:
		bufMesh = Tablet;
		break;
	}


	NewBlock->Init(logicGrid->Grid[pos.X][pos.Y].Type, logicGrid->Grid[pos.X][pos.Y].Color, bufMesh, bufmat);
	NewBlock->AttachRootComponentToActor(this);
	return NewBlock;
}

void AMainGrid::NewLevel()
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
				CreateBlock(Point(x, y), FRotator(0, 0, 0));
			}
		}
}

void AMainGrid::CreateNewTablet()
{
	LogicGrid* logicGrid = LogicGrid::Get();
	logicGrid->CreateNewTablet();

	AGameBlock* LeftPart = CreateBlock(Point(3, logicGrid->GridHeight - 1), FRotator(0, 0, -90));
	AGameBlock* RightPart = CreateBlock(Point(4, logicGrid->GridHeight - 1), FRotator(0, 0, 90));
}

void AMainGrid::PauseGame()
{ 

}

void AMainGrid::StartGame()
{
	//TODO ADD START 3 2 1 ANIMATION
}

void AMainGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (GameState) 
	{
	case GameState::Finished :
		NewLevel();
		GameState = GameState::UnPaused;
		break;
	case GameState::Paused:
		break;
	case GameState::UnPaused:
		StartGame();
		CreateNewTablet();
		GameState = GameState::Started;
		break;
	case GameState::Started:
		break;
	}
}

