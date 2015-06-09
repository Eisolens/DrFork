#include "DrFork.h"
#include "Types.h"

BlockTypes::BlockTypes()
{
	Type = BlockType::Empty;
	Color = BlockColor::None;
}

LogicBlockTypes::LogicBlockTypes()
{
	Type = BlockType::Empty;
	Color = BlockColor::None;
	Ref = nullptr;
}