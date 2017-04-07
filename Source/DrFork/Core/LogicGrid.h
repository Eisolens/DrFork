#pragma once
#include "Types.h"

class LogicGrid;
static LogicGrid* LogicGridReference = nullptr;

class DRFORK_API LogicGrid
{
	BlockColor GetRandomColor();
public:
	const static int GridWidth = 8;
	const static int GridHeight = 18;
	LogicBlockTypes Grid[GridWidth][GridHeight];

	static LogicGrid* Get(){ if (LogicGridReference == nullptr) LogicGridReference = new LogicGrid(); return LogicGridReference; };
	void MoveBlock(const Point& from, const Point& to);
	void MoveTablet(const Point& from1, const Point& to1, const Point& from2, const Point& to2);
	void ResetCell(const Point& pos);
	
	bool CreateNewTablet();

	void NewLevel(int VirusCount);

	LogicGrid();
	~LogicGrid();
};