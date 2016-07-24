#include "Food.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

void Food::respawnInNewPlace(int maxAbasoluteRandNumber) {
	srand(time(NULL));
	int randomTranslateX = (rand() % (2 * maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	int randomTranslateY = (rand() % (2 * maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	this->M = glm::translate(this->M, glm::vec3(0, 1.0f, -3));
	float newX = this->currentPosition.getX() + randomTranslateX;
	float newY = this->currentPosition.getY() + randomTranslateY;
	this->currentPosition.setX(newX);
	this->currentPosition.setY(newY);
};

Food::~Food()
{
}
