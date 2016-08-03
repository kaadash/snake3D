#pragma once
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Coordinate.h"
#include "shaderprogram.h"
class GameObject
{
protected:
	glm::mat4 M;
	GLuint *tex;
	Coordinate currentPosition;
public:
	GameObject();
	GameObject(glm::mat4 *startingWorldMatrix);
	void draw(GLuint vao, ShaderProgram *shaderProgram, glm::mat4 *V, glm::mat4 *M, glm::mat4 *P, float *objectVertices, float *objectTexCords, unsigned int vertexCount);
	void init(char *pathImage);
	void setInitPosition(float x, float y, float z);
	Coordinate *getCurrentPosition();
	Coordinate &getCurrentPosition2();
	glm::mat4 *getM();
	~GameObject();
};

