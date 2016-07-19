#ifndef MODEL_H
#define MODEL_H
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "ObjLoader.cpp"

class Model
{
public:
	Model(const char * pathToObj, glm::mat4 &M, glm::mat4 &V, glm::mat4 &P);
	void drawModel();
	glm::vec3* verticesArray = &vertices[0];

public:
	char * pathToObj;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	glm::mat4 *M;
	glm::mat4 *P;
	glm::mat4 *V;

};
#endif