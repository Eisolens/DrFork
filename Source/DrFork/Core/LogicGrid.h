#pragma once
#include "Types.h"

class LogicGrid;
static LogicGrid* LogicGridReference = nullptr;

class DRFORK_API LogicGrid
{
	BlockColor GetRandomColor();
public:
	const static int GridWidth = 8;
	const static int GridHeight = 17;
	LogicBlockTypes Grid[GridWidth][GridHeight];

	static LogicGrid* Get(){ if (LogicGridReference == nullptr) LogicGridReference = new LogicGrid(); return LogicGridReference; };
	void MoveBlock(const Point& from, const Point& to);
	void ResetCell(const Point& pos);
	
	void CreateNewTablet();

	void NewLevel();

	LogicGrid();
	~LogicGrid();
};