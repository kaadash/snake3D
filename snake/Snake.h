#pragma once
#include "GameObject.h"
using namespace std;
class Snake: public GameObject
{
public:
	Snake(glm::mat4 *startingWorldMatrix) : GameObject(startingWorldMatrix) {};
	void move();
	void rotate(float deg);
	void relativeRotate(glm::mat4 *relativeM, float degree);
	void grow();

	~Snake();
};

