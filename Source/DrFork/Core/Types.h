#pragma once

enum BlockType {
	None = 0,
	Virus,
	Tablet
};

enum BlockColor {
	Red = 0,
	Blue,
	Yellou
};

struct BlockTypes{
	BlockType Type;
	BlockColor Color;
	BlockTypes();
};
