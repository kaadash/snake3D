#include "Food.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

void Food::relativeRotate(glm::mat4 * relativeM, float degree)
{
	glm::mat4 previousState = this->M;
	this->M = glm::rotate(*relativeM, degree, glm::vec3(0, 1.0f, 0));
	const float PI = 3.141592653589793f;
	this->M = glm::translate(*relativeM, glm::vec3(this->currentPosition.getX(), 1.0f, this->currentPosition.getY()));
	
}

void Food::respawnInNewPlace(int maxAbasoluteRandNumber, GameBoard *gameBoard) {
	srand(time(NULL));
	int randomTranslateX = 2*((rand() % (2*maxAbasoluteRandNumber)) - maxAbasoluteRandNumber);
	int randomTranslateY = 2*((rand() % (2*maxAbasoluteRandNumber)) - maxAbasoluteRandNumber);
	this->M = glm::translate(*gameBoard->getM(), glm::vec3(randomTranslateX, 1, randomTranslateY));
	float newX = randomTranslateX;
	float newY = randomTranslateY;
	this->currentPosition.setX(newX);
	this->currentPosition.setY(newY);
	gameBoard->updateFoodPosition(this->currentPosition);
};

Food::~Food()
{
}
