#pragma once

class AGameBlock;

enum TabletRotState {
	Right = 0,
	Down,
	Left,
	Up
};

enum GameRoundState {
	MoveControlTablet = 0,
	DestroyBlocksRound,
	MoveUnControlTablet
};

enum GameState {
	Paused = 0,
	UnPaused,
	Started,
	Finished
};

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

struct BlockTypes {
	BlockType Type;
	BlockColor Color;
	BlockTypes();
};

struct LogicBlockTypes : public BlockTypes {
	AGameBlock * Ref;
	LogicBlockTypes();
};

struct Point {
	int X;
	int Y;
	Point(){ X = 0; Y = 0; };
	Point(int x, int y) : X(x), Y(y) {};
};