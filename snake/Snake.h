#pragma once
#include "GameObject.h"
using namespace std;
class Snake: public GameObject
{
public:
	Snake(glm::mat4 *startingWorldMatrix) : GameObject(startingWorldMatrix) {};
	void move();
	void rotate(float deg);
	void grow();

	~Snake();
};

