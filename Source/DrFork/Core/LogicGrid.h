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
	BlockTypes Grid[GridWidth][GridHeight];

	static LogicGrid* Get(){ if (LogicGridReference == nullptr) LogicGridReference = new LogicGrid(); return LogicGridReference; };

	void NewLevel();

	LogicGrid();
	~LogicGrid();
};