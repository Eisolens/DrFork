#pragma once

enum BlockType {
	Empty = 0,
	Virus,
	Tablet
};

enum BlockColor {
	None = 0,
	Red,
	Blue,
	Yellou
};

struct BlockTypes{
	BlockType Type;
	BlockColor Color;
	BlockTypes();
};

struct Point
{
	int X;
	int Y;
	Point(){ X = 0; Y = 0; };
};