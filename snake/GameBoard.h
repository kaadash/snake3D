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
	void rotate(float degree);
	void updateFoodPosition(Coordinate newCords);
	void updateSnakeHeadPosition(Coordinate newCords);
	bool comparePosition(float radius, float firstX, float secondX);
	Coordinate getFoodPosition();
	Coordinate getSnakeHeadPosition();
	bool checkIfSnakeAteFood();
	~GameBoard();
};

