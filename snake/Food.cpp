#include "Food.h"

void Food::respawnInNewPlace() {
	this->M = glm::translate(this->M, glm::vec3(2.0f, 1.0f, 2.0f));
};

Food::~Food()
{
}
