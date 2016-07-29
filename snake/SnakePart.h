#pragma once
#include <iostream>
#include "GameObject.h"
#include "GameBoard.h"
#include "Food.h"
using namespace std;
class SnakePart : public GameObject
{
private:
	float rotateValue;
	int direction;
	bool head;
public:
	SnakePart(glm::mat4 *startingWorldMatrix, bool head, int direction) : GameObject(startingWorldMatrix) {
		this->direction = direction;
		this->head = head;
	};
	void move(GameBoard *gameBoard);
	void move(Coordinate * coordinate, glm::mat4 * relativeM, float degree);
	void rotate(float deg, float direction);
	void relativeRotate(glm::mat4 *relativeM, float degree);
	void grow();
	void draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount);
	bool isHead();
	int getDirection();
	~SnakePart();
};