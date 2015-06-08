#include "DrFork.h"
#include "Settings.h"
#include "LogicGrid.h"

BlockColor LogicGrid::GetRandomColor()
{
	FRandomStream rnd;
	rnd.GenerateNewSeed();
	int32 rndNumber = rnd.RandRange(1, 3);

	switch (rndNumber)
	{
	case 1:
		return BlockColor::Red;
		break;
	case 2:
		return BlockColor::Blue;
		break;
	case 3:
		return BlockColor::Yellou;
		break;
	}
	return BlockColor::None;
}

void LogicGrid::CreateNewTablet()
{
	for (int i = 0; i < 2; i++){
		Grid[3 + i][GridHeight - 1].Type = BlockType::Tablet;
		Grid[3 + i][GridHeight - 1].Color = GetRandomColor();
	}
}

void LogicGrid::NewLevel()
{
	for (int x = 0; x < GridWidth; x++)
		for (int y = 0; y < GridHeight; y++)
		{
			Grid[x][y].Color = BlockColor::None;
			Grid[x][y].Type = BlockType::Empty;
		}
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

LogicGrid::LogicGrid()
{
}

LogicGrid::~LogicGrid()
{
}
