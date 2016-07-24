#pragma once
#include "GameObject.h"
using namespace std;
class Snake: public GameObject
{
private:
	float rotateValue;
	int direction;
public:
	Snake(glm::mat4 *startingWorldMatrix) : GameObject(startingWorldMatrix) { this->direction = 0; };
	void move();
	void rotate(float deg, float direction);
	void relativeRotate(glm::mat4 *relativeM, float degree);
	void grow();

	~Snake();
};

