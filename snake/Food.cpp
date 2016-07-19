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
	glBindTexture(GL_TEXTURE_2D, tex[0]); //Wybierz teksturê
	glEnableClientState(GL_VERTEX_ARRAY); //W³¹cz uzywanie tablicy wspó³rzêdnych wierzcho³ków
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //W³¹cz u¿ywanie tablicy wspó³rzêdnych teksturowania
	glVertexPointer(3, GL_FLOAT, 0, floorVertices); //Zdefiniuj tablicê, która jest Ÿród³em wspó³rzêdnych wierzcho³ków
	glTexCoordPointer(2, GL_FLOAT, 0, floorTexCoords); //Zdefiniuj tablicê, która jest Ÿród³em wspó³rzêdnych teksturowania
	glDrawArrays(GL_QUADS, 0, floorVertexCount); //Narysuj obiekt
	glDisableClientState(GL_VERTEX_ARRAY); //Wy³¹cz uzywanie tablicy wspó³rzêdnych wierzcho³ków
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Wy³¹cz u¿ywanie tablicy wspó³rzêdnych teksturowania

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
