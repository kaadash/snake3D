#include "Snake.h"

void Snake::init(char *pathImage) {
	this->snakeParts[0].init(pathImage);
} 
//zrobione

void Snake::setInitPosition(float x, float y, float z)
{
	this->snakeParts[0].setInitPosition(x, y, z);
} 
//zrobione 

void Snake::move(GameBoard *gameBoard, Food *food) {
	if (this->growing) this->grow();

	for (int i = length - 1; i >= 0; i--) {
		if (snakeParts[i].isHead()) {
			snakeParts[i].move(gameBoard);
		}
		else {
			snakeParts[i].move(snakeParts[i-1].getCurrentPosition());
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
	this->snakeParts[0].relativeRotate(relativeM, degree);
}

void Snake::grow() {
	glm::mat4 M = glm::mat4(1.0f);
	SnakePart snakePart(&M, false);
	snakePart.init("snakepart.png");
	this->snakeParts.push_back(snakePart);
	
	this->length++;
	this->growing = false;
} 
//zrobione - chyba

void Snake::draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount)
{
	for (auto &snakePart : snakeParts) {
		snakePart.draw(V, objectVertices, objectTexCords, vertexCount);
	}
}

Snake::~Snake()
{
}
