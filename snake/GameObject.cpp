#include "GameObject.h"
#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
GameObject::GameObject()
{
	this->M = glm::mat4(1.0f);
	this->tex = new GLuint[2];
}


GameObject::GameObject(glm::mat4 *startingWorldMatrix)
{
	this->M = *startingWorldMatrix;
	this->tex = new GLuint[2];
	this->currentPosition.setX(0);
	this->currentPosition.setY(0);
}

void GameObject::draw(glm::mat4 *V) {
	unsigned int cubeVertexCount = 24;
	float cubeVertices[]{
		-1,-1,-1,
		1,-1,-1,
		1,1,-1,
		-1,1,-1,

		-1,-1,1,
		1,-1,1,
		1,1,1,
		-1,1,1,

		-1,-1,-1,
		1,-1,-1,
		1,-1,1,
		-1,-1,1,

		-1,1,-1,
		1,1,-1,
		1,1,1,
		-1,1,1,

		-1,-1,-1,
		-1,-1,1,
		-1,1,1,
		-1,1,-1,

		1,-1,-1,
		1,-1,1,
		1,1,1,
		1,1,-1
	};

	float cubeTexCoords[] = {
		0,0, 1,0, 1,1, 0,1,
	};


	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(*V * this->M));

	glBindTexture(GL_TEXTURE_2D, this->tex[0]); //Wybierz tekstur�
	glEnableClientState(GL_VERTEX_ARRAY); //W��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //W��cz u�ywanie tablicy wsp�rz�dnych teksturowania
	glVertexPointer(3, GL_FLOAT, 0, cubeVertices); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych wierzcho�k�w
	glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych teksturowania
	glDrawArrays(GL_QUADS, 0, cubeVertexCount); //Narysuj obiekt
	glDisableClientState(GL_VERTEX_ARRAY); //Wy��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Wy��cz u�ywanie tablicy wsp�rz�dnych teksturowania
}
void GameObject::init(char *pathImage) {
	std::vector<unsigned char> image[2];   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
	unsigned imageTextureLoadingStatus = lodepng::decode(image[0], width, height, pathImage);

	glGenTextures(1, &this->tex[0]); //Zainicjuj dwa uchwyty
	glBindTexture(GL_TEXTURE_2D, this->tex[0]); //Uaktywnij uchwyt
												//Wczytaj obrazek do pami?ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image[0].data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
}

GameObject::~GameObject()
{
}
