#include "Food.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

void Food::respawnInNewPlace(int maxAbasoluteRandNumber) {
	srand(time(NULL));
	int randomTranslateX = (rand() % (2 * maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	int randomTranslateY = (rand() % (2*maxAbasoluteRandNumber)) - maxAbasoluteRandNumber;
	this->M = glm::translate(this->M, glm::vec3(randomTranslateX, 1.0f, randomTranslateY));
};

Food::~Food()
{
}
