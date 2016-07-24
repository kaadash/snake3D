#include "Food.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

void Food::respawnInNewPlace(int maxAbasoluteRandNumber, GameBoard *gameBoard) {
	srand(time(NULL));
	int randomTranslateX = (rand() % (2 * maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	int randomTranslateY = (rand() % (2 * maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	this->M = glm::translate(*gameBoard->getM(), glm::vec3(randomTranslateX, 1, randomTranslateY));
	float newX = this->currentPosition.getX() + randomTranslateX;
	float newY = this->currentPosition.getY() + randomTranslateY;
	this->currentPosition.setX(newX);
	this->currentPosition.setY(newY);
	gameBoard->updateFoodPosition(this->currentPosition);
};

Food::~Food()
{
}
