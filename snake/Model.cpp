#include "model.h"


Model::Model(const char *pathToObj, glm::mat4 &M, glm::mat4 &V, glm::mat4 &P)
{
	this->M = &M;
	this->V = &V;
	this->P = &P;
	loadOBJ(pathToObj, this->vertices, this->uvs, this->normals);
}

void Model::drawModel()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	// Clear the screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 MVP = (*M) * (*V) * (*P);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(*this->P));
	glMatrixMode(GL_MODELVIEW);
	
	//*this->M = rotate(*this->M, 0.01f, glm::vec3(1, 0, 0));
	//float multiplier = (std::rand() % 100) / 1000;
	//*this->M = glm::translate(*this->M, glm::vec3(multiplier, 0.01f, 0.01f));

	//glLoadMatrixf(value_ptr(*this->V**this->M));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}
