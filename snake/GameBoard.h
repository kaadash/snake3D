#pragma once
#include "Coordinate.h"
#include "GameObject.h"
class GameBoard : public GameObject
{
private:
	Coordinate foodPosition;
	Coordinate snakeHeadPosition;

public:
	GameBoard();
	~GameBoard();
};

