#pragma once
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
	SnakePart(glm::mat4 *startingWorldMatrix, bool head) : GameObject(startingWorldMatrix) {
		this->direction = 0;
		this->head = head;
	};
	void move(GameBoard *gameBoard);
	void move(Coordinate *coordinate);
	void rotate(float deg, float direction);
	void relativeRotate(glm::mat4 *relativeM, float degree);
	void grow();
	void draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount);
	bool isHead();
	~SnakePart();
};