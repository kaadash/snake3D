#include "Snake.h"

void Snake::move() {
	int moveValue = 0.01;
	x += 0.01;
	this->M = glm::translate(this->M, glm::vec3(0.01f, 0, 0));
}



Snake::~Snake()
{
}
