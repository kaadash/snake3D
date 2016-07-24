#pragma once
#include "GameObject.h"
#include "GameBoard.h"
class Food : public GameObject
{
public:
	Food() : GameObject() {}
	Food(glm::mat4 *startingWorldMatrix) : GameObject(startingWorldMatrix) {};


	void respawnInNewPlace(int maxRandomNumber, GameBoard *gameBoard);
	~Food();
};

