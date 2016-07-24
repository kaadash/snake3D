#pragma once
#include "Coordinate.h"
class GameBoard
{
private:
	Coordinate foodPosition;
	Coordinate snakeHeadPosition;

public:
	GameBoard();
	void draw();
	~GameBoard();
};

