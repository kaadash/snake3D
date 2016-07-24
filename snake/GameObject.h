#pragma once
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Coordinate.h"
class GameObject
{
protected:
	glm::mat4 M;
	GLuint *tex;
	Coordinate currentPosition;
public:
	GameObject();
	GameObject(glm::mat4 *startingWorldMatrix);
	void draw(glm::mat4 *V);
	void init(char *pathImage);
	~GameObject();
};

