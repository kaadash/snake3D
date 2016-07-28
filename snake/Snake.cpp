#include "Snake.h"

void Snake::move(GameBoard *gameBoard, Food *food) {
	int moveValue = 2;
	float newPositionX = 0;
	float newPositionY = 0;
	//moving on axis X
	if (this->direction % 2 == 0) {
		//forward
		if (this->direction == 0) {
			newPositionX = this->currentPosition.getX() + 2;
		}
		//backward
		else {
			newPositionX = this->currentPosition.getX() - 2;
			//this->M = glm::translate(this->M, glm::vec3(-0.01f, 0, 0));
		}
		this->currentPosition.setX(newPositionX);
	}
	//moving on axis Y
	else {
		if (this->direction == 1 || this->direction == -3) {
			newPositionY = this->currentPosition.getY() - 2;
			//this->M = glm::translate(this->M, glm::vec3(0, 0, -0.01));
		}
		else {
			newPositionY = this->currentPosition.getY() + 2;
			//this->M = glm::translate(this->M, glm::vec3(0, 0, 0.01));
		}
		this->currentPosition.setY(newPositionY);
	}
	this->M = glm::translate(this->M, glm::vec3(2.0f, 0, 0));
	gameBoard->updateSnakeHeadPosition(this->currentPosition);
	if (gameBoard->checkIfSnakeAteFood()) {
		food->respawnInNewPlace(4, gameBoard);
	}

}

void Snake::rotate(float degree, float direction) {
	this->direction += direction;
	if (this->direction == 4 || this->direction == -4) {
		this->direction = 0;
	}
	this->M = glm::rotate(this->M, degree, glm::vec3(0, 1.0f, 0));
}

void Snake::relativeRotate(glm::mat4 *relativeM, float degree) {
	glm::mat4 previousState = this->M;
	this->M = glm::rotate(*relativeM, degree, glm::vec3(0, 1.0f, 0));
	const float PI = 3.141592653589793f;
	this->M = glm::translate(*relativeM, glm::vec3(this->currentPosition.getX(), 1.0f, this->currentPosition.getY()));
	if (this->direction % 2 == 0) {
		//forward
		if (this->direction == 0) {
			this->M = glm::rotate(this->M, 0.0f, glm::vec3(0, 1.0f, 0));
		}
		//backward
		else {
			this->M = glm::rotate(this->M, PI, glm::vec3(0, 1.0f, 0));
		}
	}
	//moving on axis Y
	else {
		if (this->direction == 1 || this->direction == -3) {
			this->M = glm::rotate(this->M, PI / 2, glm::vec3(0, 1.0f, 0));
		}
		else {
			this->M = glm::rotate(this->M, -PI / 2, glm::vec3(0, 1.0f, 0));
		}
	}
}

void Snake::grow() {

}

void Snake::draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount)
{
	GameObject::draw(V, objectVertices, objectTexCords, vertexCount);
}

Snake::~Snake()
{
}
