#include "DrFork.h"
#include "MainGrid.h"
#include "GameBlock.h"
#include "Settings.h"

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
	AGameBlock* NewBlock = GetWorld()->SpawnActor<AGameBlock>(FVector(pos.Y * BlockSize, pos.X * BlockSize, 0), rot);
	LogicGrid.Grid[pos.X][pos.Y].Ref = NewBlock;
	NewBlock->Pos = pos;

	UMaterialInstance* bufmat = nullptr;

	switch (LogicGrid.Grid[pos.X][pos.Y].Color)
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

	switch (LogicGrid.Grid[pos.X][pos.Y].Type)
	{
	case BlockType::Virus:
		bufMesh = Virus;
		break;

	case BlockType::Tablet:
		bufMesh = Tablet;
		break;
	}


	NewBlock->Init(LogicGrid.Grid[pos.X][pos.Y].Type, LogicGrid.Grid[pos.X][pos.Y].Color, bufMesh, bufmat);
	NewBlock->AttachRootComponentToActor(this);
	return NewBlock;
}

void AMainGrid::NewLevel()
{
	for (auto chield : this->Children)
		chield->Destroy();

	LogicGrid.NewLevel();

	for (int x = 0; x < LogicGrid.GridWidth; x++)
		for (int y = 0; y < LogicGrid.GridHeight; y++)
		{
			if (LogicGrid.Grid[x][y].Type == BlockType::Virus)
			{
				CreateBlock(Point(x, y), FRotator(0, 0, 0));
			}
		}
}

void AMainGrid::CreateNewTablet()
{
	LogicGrid.CreateNewTablet();

	AGameBlock* LeftPart = CreateBlock(Point(3, LogicGrid.GridHeight - 1), FRotator(0, 0, -90));
	AGameBlock* RightPart = CreateBlock(Point(4, LogicGrid.GridHeight - 1), FRotator(0, 0, 90));
	LeftPart->SetOutline(true);
	RightPart->SetOutline(true);
	LeftPart->Link = RightPart;
	RightPart->Link = LeftPart;
	this->ControlledTablet = LeftPart;
}

void AMainGrid::DropTablet(float DeltaTime)
{
	if (ControlledTablet != nullptr)
	{
		CollectedTime += DeltaTime;
		Settings* Settings = Settings::Get();
		if (CollectedTime >= Settings->Speed)
		{
			CollectedTime -= Settings->Speed;
			if (CheckMoveBlock(ControlledTablet, 0, -1))
			{
				MoveBlock(ControlledTablet, 0, -1);
			} else {
				ControlledTablet->SetOutline(false);
				if (ControlledTablet->Link != nullptr)
					ControlledTablet->Link->SetOutline(false);
				ControlledTablet = nullptr;
			}
		}
	} else {
		//TODO DELETE ROUND
		//     / \
		//      |
		//     \ /
		//TODO MOVE ROUNT
		//TODO then create tablet
		CreateNewTablet();
	}
}

void AMainGrid::MoveBlock(AGameBlock* block, int diffX, int diffY)
{
	block->SetActorRelativeLocation(FVector((block->Pos.Y + diffY) * BlockSize, (block->Pos.X + diffX) * BlockSize, 0));
	LogicGrid.MoveBlock(block->Pos, Point(block->Pos.X, block->Pos.Y - 1));
	block->Pos.Y -= 1;
	if (block->Link != nullptr){
		block->Link->SetActorRelativeLocation(FVector((block->Link->Pos.Y + diffY) * BlockSize, (block->Link->Pos.X + diffX) * BlockSize, 0));
		LogicGrid.MoveBlock(block->Link->Pos, Point(block->Link->Pos.X, block->Link->Pos.Y - 1));
		block->Link->Pos.Y -= 1;
	}
}

bool AMainGrid::CheckMoveBlock(AGameBlock* block, int diffX, int diffY)
{
	if (!CheckIndexes(block, diffX, diffY))
		return false;

	LogicBlockTypes& refCell = LogicGrid.Grid[block->Pos.X + diffX][block->Pos.Y + diffY];

	switch (refCell.Type){
	case BlockType::Empty :
		return CeckMoveBlockChield(block, diffX, diffY);
		break;
	case BlockType::Tablet :
		if (CheckMoveBlock(refCell.Ref, 0, -1)){
			return CeckMoveBlockChield(block, diffX, diffY);
		} else {
			return false;
		}
		break;
	case BlockType::Virus :
		return false;
		break;
	}
	return false;
}

bool AMainGrid::CeckMoveBlockChield(AGameBlock* block, int diffX, int diffY)
{
	if (block->Link != nullptr)
	{
		if (!CheckIndexes(block->Link, diffX, diffY))
			return false;

		LogicBlockTypes& refCell = LogicGrid.Grid[block->Link->Pos.X + diffX][block->Link->Pos.Y + diffY];

		switch (refCell.Type){
		case BlockType::Empty:
			return true;
			break;
		case BlockType::Tablet:
			if (block->Link->Link == block)
				return true;
			return CheckMoveBlock(refCell.Ref, 0, -1);
			break;
		case BlockType::Virus:
			return false;
			break;
		}
		return false;
	}
	else {
		return true;
	}
}

bool AMainGrid::CheckIndexes(AGameBlock* block, int diffX, int diffY)
{
	if (block->Pos.X + diffX < 0)
		return false;
	if (block->Pos.X + diffX > LogicGrid.GridWidth - 1)
		return false;
	if (block->Pos.Y + diffY < 0)
		return false;
	if (block->Pos.Y + diffY > LogicGrid.GridHeight - 1)
		return false;
	return true;
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
		DropTablet(DeltaTime);
		break;
	}
}

