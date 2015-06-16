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
	GameRoundState = GameRoundState::MoveControlTablet;
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
			if (LogicGrid.Grid[x][y].Type == BlockType::Virus)
				CreateBlock(Point(x, y), FRotator(0, 0, 0));
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

void AMainGrid::SetBlockActorPosition(AGameBlock* block, int diffX, int diffY)
{
	block->SetActorRelativeLocation(FVector((block->Pos.Y + diffY) * BlockSize, (block->Pos.X + diffX) * BlockSize, 0));
	LogicGrid.MoveBlock(block->Pos, Point(block->Pos.X + diffX, block->Pos.Y + diffY));
	block->Pos.Y += diffY;
	block->Pos.X += diffX;
}

void AMainGrid::SetTabletActorPosition(AGameBlock* block, int diffX, int diffY)
{
	AGameBlock* chield = block->Link;

	block->SetActorRelativeLocation(FVector((block->Pos.Y + diffY) * BlockSize, (block->Pos.X + diffX) * BlockSize, 0));
	chield->SetActorRelativeLocation(FVector((chield->Pos.Y + diffY) * BlockSize, (chield->Pos.X + diffX) * BlockSize, 0));

	Point blockPos = Point(block->Pos.X + diffX, block->Pos.Y + diffY);
	Point chieldPos = Point(chield->Pos.X + diffX, chield->Pos.Y + diffY);

	LogicGrid.MoveTablet(block->Pos, blockPos, chield->Pos, chieldPos);

	block->Pos = blockPos;
	chield->Pos = chieldPos;
}

void AMainGrid::RotateTabletActor(AGameBlock* block)
{
	FRotator rot = block->GetActorRotation();
	block->SetActorRotation(FRotator(rot.Pitch,rot.Yaw + 90,rot.Roll));

	rot = block->Link->GetActorRotation();
	block->Link->SetActorRotation(FRotator(rot.Pitch, rot.Yaw + 90, rot.Roll));
}

void AMainGrid::GameCycle(float DeltaTime)
{
	CollectedTime += DeltaTime;
	switch (GameRoundState)
	{
	case MoveControlTablet:
		MoveControlledTablet();
		break;
	case DestroyBlocksRound:
		if(DestroyRound())
			if (CheckMoveRound())
				GameRoundState = GameRoundState::MoveUnControlTablet;
			else
				GameRoundState = GameRoundState::MoveControlTablet;
			break;
	case MoveUnControlTablet:
		MoveUncontrolledTablet();
		break;
	}
}

void AMainGrid::MoveUncontrolledTablet()
{
	if (CollectedTime >= Settings::Get()->Speed * 0.8f)
	{
		CollectedTime -= Settings::Get()->Speed * 0.8f;
		GameRoundState = GameRoundState::DestroyBlocksRound;
		for (int i = 0; i < LogicGrid.GridWidth; i++)
			for (int j = 1; j < LogicGrid.GridHeight; j++)
				if (LogicGrid.Grid[i][j].Type == BlockType::Tablet)
					if (LogicGrid.Grid[i][j].Ref->IsCanMove)
					{
						LogicGrid.Grid[i][j].Ref->IsCanMove = false;
						SetBlockActorPosition(LogicGrid.Grid[i][j].Ref, 0, -1);
						//TODO ADD DROP SOUND
					}
	}
}

void AMainGrid::MoveControlledTablet()
{
	if (ControlledTablet != nullptr)
	{
		Settings* Settings = Settings::Get();
		if (CollectedTime >= Settings->GetUnControlledSpeed())
		{
			CollectedTime -= Settings->GetUnControlledSpeed();
			if (CheckMoveBlock(ControlledTablet, 0, -1))
			{
				SetTabletActorPosition(ControlledTablet, 0, -1);
			}
			else 
			{
				ControlledTablet->SetOutline(false);
				if (ControlledTablet->Link != nullptr)
					ControlledTablet->Link->SetOutline(false);
				ControlledTablet = nullptr;
				GameRoundState = GameRoundState::DestroyBlocksRound;
			}
		}
	}
	else
	{
		CreateNewTablet();
	}
}

bool AMainGrid::CheckMoveRound()
{
	bool ret = false;
	for (int i = 0; i < LogicGrid.GridWidth; i++)
		for (int j = 1; j < LogicGrid.GridHeight; j++)
			if (LogicGrid.Grid[i][j].Type == BlockType::Tablet)
				if (LogicGrid.Grid[i][j].Ref->Link == nullptr)
					if (CheckIndexes(LogicGrid.Grid[i][j].Ref, 0, -1))
						switch (LogicGrid.Grid[i][j - 1].Type)
						{
						case BlockType::Empty :
							LogicGrid.Grid[i][j].Ref->IsCanMove = true;
							ret = true;
							break;
						case BlockType::Tablet :
							if (LogicGrid.Grid[i][j - 1].Ref->IsCanMove)
								LogicGrid.Grid[i][j].Ref->IsCanMove = true;
							break;
						}
	return ret;
}

bool AMainGrid::DestroyRound()
{
	struct DeleteElements
	{
		Point From;
		Point To;
		DeleteElements(const Point& from, const Point& to) :From(from), To(to){};
	};
	TArray<DeleteElements> delElem;
	
	for (int i = 0; i < LogicGrid.GridWidth; i++)
	{
		Point from = Point(i, 0);
		Point to = from;
		for (int j = 1; j < LogicGrid.GridHeight; j++)
		{
			LogicBlockTypes* cell = &LogicGrid.Grid[i][j];
			
			if (LogicGrid.Grid[from.X][from.Y].Type == BlockType::Empty)
			{
				from = Point(i, j);
				continue;
			}

			if (cell->Color == LogicGrid.Grid[from.X][from.Y].Color)
			{
				to = Point(i, j);
			}
			else 
			{
				if (FMath::Abs(from.X - to.X) >= 3 || FMath::Abs(from.Y - to.Y) >= 3)
					delElem.Add(DeleteElements(from, to));
				from = Point(i, j);
			}
		}
	}

	for (int j = 0; j < LogicGrid.GridHeight; j++)
	{
		Point from = Point(0, j);
		Point to = from;
		for (int i = 1; i < LogicGrid.GridWidth; i++)
		{
			LogicBlockTypes* cell = &LogicGrid.Grid[i][j];

			if (LogicGrid.Grid[from.X][from.Y].Type == BlockType::Empty)
			{
				from = Point(i, j);
				continue;
			}

			if (cell->Color == LogicGrid.Grid[from.X][from.Y].Color)
			{
				to = Point(i, j);
			}
			else
			{
				if (FMath::Abs(from.X - to.X) >= 3 || FMath::Abs(from.Y - to.Y) >= 3)
					delElem.Add(DeleteElements(from, to));
				from = Point(i, j);
			}
		}
	}

	for (auto del : delElem)
		for (int i = del.From.X; i <= del.To.X; i++)
			for (int j = del.From.Y; j <= del.To.Y; j++)
				if (LogicGrid.Grid[i][j].Ref != nullptr)
				{
					AGameBlock* block = LogicGrid.Grid[i][j].Ref;
					if (block->Link != nullptr)
						block->Link->Link = nullptr;
					//TODO ADD DESTROY ANIMATION
					block->Destroy();
					LogicGrid.ResetCell(Point(i, j));
				}
	if (delElem.Num() > 0)
		return true;
	else
		return false;
}

void AMainGrid::RotateTablet()
{
	if (ControlledTablet == nullptr)
		return;
	Point diff;

	switch (ControlledTablet->RotState)
	{
	case TabletRotState::Right:
		diff = Point(-1,-1);
		break;
	case TabletRotState::Down:
		diff = Point(-1, 1);
		break;
	case TabletRotState::Left:
		diff = Point(1, 1);
		break;
	case TabletRotState::Up:
		diff = Point(1, -1);
		break;
	}
	if (CeckMoveBlockChield(ControlledTablet, diff.X, diff.Y))
	{
		SetBlockActorPosition(ControlledTablet->Link, diff.X, diff.Y);
		RotateTabletActor(ControlledTablet);
		ControlledTablet->RotState = TabletRotState((int(ControlledTablet->RotState) + 1) % 4);
	}
}

void AMainGrid::MoveTablet(int32 diffX, int32 diffY)
{
	if (ControlledTablet == nullptr)
		return;
	if (CheckMoveBlock(this->ControlledTablet, diffX, diffY))
		SetTabletActorPosition(ControlledTablet, diffX, diffY);
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
		if (block == refCell.Ref->Link)
			return CeckMoveBlockChield(block, diffX, diffY);
		return false;
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
			if (block->Link == refCell.Ref->Link)
				return true;
			return false;
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
	//TODO MAKE PAUSE
}

void AMainGrid::StartGame()
{
	//TODO ADD START 3 2 1 ANIMATION
	GameState = GameState::Started;
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
		break;
	case GameState::Started:
		GameCycle(DeltaTime);
		break;
	}
}

