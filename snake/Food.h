#pragma once
#include "main.h"

class Food
{
private:
	//float vertices[12];
	//float colors[12];
	//float texCords[8];
	//float cubeVertices[72];
	//float cubeTexCords[8];
	glm::mat4 M;
public:
	Food();
	void respawnInRandomPlace(glm::mat4 *V, float height, float width);
	void draw(glm::mat4 *V);
	~Food();
};

