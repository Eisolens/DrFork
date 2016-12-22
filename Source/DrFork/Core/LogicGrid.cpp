#include "DrFork.h"
#include "Settings.h"
#include "LogicGrid.h"

BlockColor LogicGrid::GetRandomColor()
{
	FRandomStream rnd;
	rnd.GenerateNewSeed();
	return BlockColor(rnd.RandRange(1, 3));
}

bool LogicGrid::CreateNewTablet()
{
	if (Grid[3][GridHeight - 1].Ref)
		return false;

	for (int i = 0; i < 2; i++){
		Grid[3 + i][GridHeight - 1].Type = BlockType::Tablet;
		Grid[3 + i][GridHeight - 1].Color = GetRandomColor();
	}
	return true;
}

void LogicGrid::NewLevel()
{
	for (int x = 0; x < GridWidth; x++)
		for (int y = 0; y < GridHeight; y++)
			ResetCell(Point(x, y));

	Settings* settings = Settings::Get();
	settings->IncreaseComplexity();

	int maxHeight = 2;
	while ((maxHeight + 1) * GridWidth < settings->VirusCount * 2.5f)
	{
		maxHeight++;
		if (maxHeight == 12)
		{
			//TODO win game
		}
	}

	for (int i = 0; i < settings->VirusCount; i++)
	{
		FRandomStream rnd;
		rnd.GenerateNewSeed();
		bool compleate = false;

		while (!compleate)
		{
			int x = rnd.RandRange(0, GridWidth - 1);
			int y = rnd.RandRange(0, maxHeight);
			if (Grid[x][y].Type == BlockType::Empty)
			{
				compleate = true;
				Grid[x][y].Type = BlockType::Virus;
				Grid[x][y].Color = GetRandomColor();
			}
		}
	
	}
}

void LogicGrid::MoveBlock(const Point& from, const Point& to)
{
	Grid[to.X][to.Y] = Grid[from.X][from.Y];
	ResetCell(from);
}

void LogicGrid::MoveTablet(const Point& from1, const Point& to1, const Point& from2, const Point& to2)
{
	LogicBlockTypes buf1 = Grid[from1.X][from1.Y];
	LogicBlockTypes buf2 = Grid[from2.X][from2.Y];

	ResetCell(from1);
	ResetCell(from2);

	Grid[to1.X][to1.Y] = buf1;
	Grid[to2.X][to2.Y] = buf2;
}

void LogicGrid::ResetCell(const Point& pos)
{
	Grid[pos.X][pos.Y].Color = BlockColor::None;
	Grid[pos.X][pos.Y].Type = BlockType::Empty;
	Grid[pos.X][pos.Y].Ref = nullptr;
}

LogicGrid::LogicGrid()
{
	LogicGridReference = this;
}

LogicGrid::~LogicGrid()
{
}
