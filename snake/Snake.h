#pragma once
#include "GameObject.h"
class Snake: public GameObject
{
public:
	Snake(glm::mat4 *startingWorldMatrix) : GameObject(startingWorldMatrix) {};
	void move();
	~Snake();
};

