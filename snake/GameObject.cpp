#include "GameObject.h"
#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

GameObject::GameObject()
{
	this->M = glm::mat4(1.0f);

}


GameObject::GameObject(glm::mat4 *startingWorldMatrix)
{
	this->M = *startingWorldMatrix;

	this->currentPosition.setX(0);
	this->currentPosition.setY(0);
}

void GameObject::draw(glm::mat4 *V, float *objectVertices, float *objectTexCords, unsigned int vertexCount)  {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(*V * this->M));

	glBindTexture(GL_TEXTURE_2D, this->tex); //Wybierz tekstur�
	glEnableClientState(GL_VERTEX_ARRAY); //W��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //W��cz u�ywanie tablicy wsp�rz�dnych teksturowania
	glVertexPointer(3, GL_FLOAT, 0, objectVertices); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych wierzcho�k�w
	glTexCoordPointer(2, GL_FLOAT, 0, objectTexCords); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych teksturowania
	glDrawArrays(GL_QUADS, 0, vertexCount); //Narysuj obiekt
	glDisableClientState(GL_VERTEX_ARRAY); //Wy��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Wy��cz u�ywanie tablicy wsp�rz�dnych teksturowania
}

void GameObject::draw2(glm::mat4 *V) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(*V * this->M));
	glBindTexture(GL_TEXTURE_2D, this->tex);
	this->model.drawModel();
}

void GameObject::init(char *pathImage) {
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
	unsigned imageTextureLoadingStatus = lodepng::decode(image, width, height, pathImage);

	glGenTextures(1, &this->tex); //Zainicjuj dwa uchwyty
	glBindTexture(GL_TEXTURE_2D, this->tex); //Uaktywnij uchwyt
												//Wczytaj obrazek do pami?ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
}

void GameObject::init2(char *pathImage, char *pathObj) {
	this->model.init(pathObj, this->M);

	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
	unsigned imageTextureLoadingStatus = lodepng::decode(image, width, height, pathImage);

	glGenTextures(1, &this->tex); //Zainicjuj dwa uchwyty
	glBindTexture(GL_TEXTURE_2D, this->tex); //Uaktywnij uchwyt
												//Wczytaj obrazek do pami?ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
	
	
}

void GameObject::setInitPosition(float x, float y, float z) {
	this->M = glm::translate(this->M, glm::vec3(x, y, z));
}

Coordinate *GameObject::getCurrentPosition()
{
	return &this->currentPosition;
}

Coordinate & GameObject::getCurrentPosition2()
{
	return this->currentPosition;
}

glm::mat4 *GameObject::getM() {
	return &this->M;
}


GameObject::~GameObject()
{
}
