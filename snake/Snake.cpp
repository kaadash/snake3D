#include "Snake.h"

void Snake::init(char *pathImage) {
	this->snakeParts[0].init(pathImage);
} 

void Snake::setInitPosition(float x, float y, float z)
{
	this->snakeParts[0].setInitPosition(x, y, z);
} 

void Snake::move(GameBoard *gameBoard, Food *food) {
	if (this->growing) this->grow();

	for (int i = length - 1; i >= 0; i--) {
		if (snakeParts[i].isHead()) {
			snakeParts[i].move(gameBoard);
		}
		else {
			snakeParts[i].move(snakeParts[i-1].getCurrentPosition(), gameBoard->getM(), gameBoard->getDegree());
		}
	}
	
	if (gameBoard->checkIfSnakeAteFood()) {
		food->respawnInNewPlace(4, gameBoard);
		this->growing = true;
	}
}

void Snake::rotate(float degree, float direction) {
	this->snakeParts[0].rotate(degree, direction);
}

void Snake::relativeRotate(glm::mat4 *relativeM, float degree) {
	for (auto &snakePart : snakeParts) {
		snakePart.relativeRotate(relativeM, degree);
	}
}

void Snake::grow() {
	glm::mat4 M = glm::mat4(1.0f);
	SnakePart snakePart(&M, false, snakeParts[length-1].getDirection());
	snakePart.init("snakepart.png");
	this->snakeParts.push_back(snakePart);
	
	this->length++;
	this->growing = false;
} 

void Snake::draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount)
{
	for (auto &snakePart : snakeParts) {
		snakePart.draw(V, objectVertices, objectTexCords, vertexCount);
	}
}

Snake::~Snake()
{
}
