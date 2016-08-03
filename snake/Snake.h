#pragma once
#include <vector>
#include "GameObject.h"
#include "GameBoard.h"
#include "Food.h"
#include "SnakePart.h"
using namespace std;
class Snake
{
private:
	float rotateValue;
	int direction;
	std::vector <SnakePart> snakeParts;
	int length;
	bool growing;
	short turn;
	const float PI = 3.141592653589793f;

public:
	Snake(glm::mat4 *startingWorldMatrix) { 
		this->growing = false;
		this->direction = 0;
		SnakePart snakePart(startingWorldMatrix, true, 0);
		this->snakeParts.push_back(snakePart);
		this->length = 1;
	};
	void move(GameBoard *gameBoard, Food *food);
	void rotate(float deg, float direction);
	void relativeRotate(glm::mat4 *relativeM, float degree);
	void grow();
	void draw(GLuint vao, ShaderProgram *shaderProgram, glm::mat4 *V, glm::mat4 *M, glm::mat4 *P, float *objectVertices, float *objectTexCords, unsigned int vertexCount);
	void init(char *pathImage);
	void setInitPosition(float x, float y, float z);
	void turnLeft();
	void turnRight();
	void dontTurn();
	short getTurn();
	std::vector <SnakePart> getSnakeParts();
	~Snake();
};