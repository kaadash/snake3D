#include "Food.h"
#include "myFloor.h"

extern unsigned int floorVertexCount;
extern unsigned int tex[];
extern float floorTexCoords[];
extern float floorVertices[];



Food::Food()
{
	this->M = glm::mat4(1.0f);
}

void Food::draw(glm::mat4 *V) {
	glBindTexture(GL_TEXTURE_2D, tex[0]); //Wybierz tekstur�
	glEnableClientState(GL_VERTEX_ARRAY); //W��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //W��cz u�ywanie tablicy wsp�rz�dnych teksturowania
	glVertexPointer(3, GL_FLOAT, 0, floorVertices); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych wierzcho�k�w
	glTexCoordPointer(2, GL_FLOAT, 0, floorTexCoords); //Zdefiniuj tablic�, kt�ra jest �r�d�em wsp�rz�dnych teksturowania
	glDrawArrays(GL_QUADS, 0, floorVertexCount); //Narysuj obiekt
	glDisableClientState(GL_VERTEX_ARRAY); //Wy��cz uzywanie tablicy wsp�rz�dnych wierzcho�k�w
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Wy��cz u�ywanie tablicy wsp�rz�dnych teksturowania

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(*V * this->M));
};

void Food::respawnInRandomPlace(glm::mat4 *V, float height, float width) {
	srand(static_cast <unsigned> (time(0)));
	float position = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (height)));
	this->M = glm::mat4();
	this->draw(V);
};

Food::~Food()
{
}
