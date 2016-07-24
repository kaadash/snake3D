#include "Snake.h"

void Snake::move() {
	int moveValue = 0.01;
	float newPositionX = this->currentPosition.getX() + 0.01;
	this->currentPosition.setX(newPositionX);
	this->M = glm::translate(this->M, glm::vec3(0.01f, 0, 0));
}

void Snake::rotate(float degree) {
	this->M = glm::rotate(this->M, degree, glm::vec3(0, 1.0f, 0));
}

void Snake::grow() {

}



Snake::~Snake()
{
}
