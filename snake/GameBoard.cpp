#include "GameBoard.h"



GameBoard::GameBoard()
{
}

void GameBoard::updateFoodPosition(Coordinate newCords) {
	this->foodPosition.updateCords(newCords);
}

void GameBoard::updateSnakeHeadPosition(Coordinate newCords) {
	this->snakeHeadPosition.updateCords(newCords);
}

Coordinate GameBoard::getFoodPosition() {
	return this->foodPosition;
}
Coordinate GameBoard::getSnakeHeadPosition() {
	return this->snakeHeadPosition;
}

bool GameBoard::comparePosition(float radius, float firstX, float secondX) {
	return (firstX <= secondX + radius && firstX >= secondX - radius);

}

bool GameBoard::checkIfSnakeAteFood() {
	const float radius = 0.4;
	bool comparedX = comparePosition(radius, this->foodPosition.getX(), this->snakeHeadPosition.getX());
	bool comparedY = comparePosition(radius, this->foodPosition.getY(), this->snakeHeadPosition.getY());
	return (comparedX && comparedY);
}

float GameBoard::getDegree()
{
	return this->degree;
}

void GameBoard::rotate(float degree) {
	this->M = glm::rotate(this->M, degree, glm::vec3(0, 1.0f, 0));
	this->degree += degree;
}

GameBoard::~GameBoard()
{
}
