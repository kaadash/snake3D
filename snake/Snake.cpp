#include "Snake.h"

void Snake::move() {
	int moveValue = 0.01;
	float newPositionX = 0;
	float newPositionY = 0;
	//moving on axis X
	if (this->direction % 2 == 0) {
		//forward
		if (this->direction == 0) {
			newPositionX = this->currentPosition.getX() + 0.01;
			this->M = glm::translate(this->M, glm::vec3(0.01f, 0, 0));
		}
		//backward
		else {
			newPositionX = this->currentPosition.getX() - 0.01;
			this->M = glm::translate(this->M, glm::vec3(-0.01f, 0, 0));
		}
		this->currentPosition.setX(newPositionX);
	}
	//moving on axis Y
	else {
		if (this->direction == 1 || this->direction == -3) {
			newPositionY = this->currentPosition.getY() - 0.01;
			this->M = glm::translate(this->M, glm::vec3(0, 0, -0.01));
		}
		else {
			newPositionY = this->currentPosition.getY() + 0.01;
			this->M = glm::translate(this->M, glm::vec3(0, 0, 0.01));
		}
		this->currentPosition.setY(newPositionY);
	}
}

void Snake::rotate(float degree, float direction) {
	this->direction += direction;
	if (this->direction == 4 || this->direction == -4) {
		this->direction = 0;
	}
	//this->M = glm::rotate(this->M, degree, glm::vec3(0, 1.0f, 0));
}

void Snake::relativeRotate(glm::mat4 *relativeM, float degree) {
	glm::mat4 previousState = this->M;
	this->M = glm::rotate(*relativeM, degree, glm::vec3(0, 1.0f, 0));
	this->M = glm::translate(*relativeM, glm::vec3(this->currentPosition.getX(), 0, this->currentPosition.getY()));
}


void Snake::grow() {

}



Snake::~Snake()
{
}
