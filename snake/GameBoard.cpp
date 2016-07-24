#include "GameBoard.h"



GameBoard::GameBoard()
{
}


void GameBoard::rotate(float degree) {
	this->M = glm::rotate(this->M, degree, glm::vec3(0, 1.0f, 0));
}

GameBoard::~GameBoard()
{
}
