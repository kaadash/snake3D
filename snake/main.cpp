#include "main.h"
float speed = 0;

glm::mat4 M2 = glm::mat4(1.0f);
Food apple;
Snake snake(&M2);


void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed = -0.01f;
		if (key == GLFW_KEY_RIGHT) speed = 0.01f;
		if (key == GLFW_KEY_A) M2 = glm::rotate(M2, PI / 2, glm::vec3(0, 1.0f, 0));
		if(key == GLFW_KEY_D) M2 = glm::rotate(M2, -PI / 2, glm::vec3(0, 1.0f, 0));
	}

	if (action == GLFW_RELEASE) {
		speed = 0;
	}
}


//glm::mat4 newM3 = glm::mat4(1.0f);
//Model obj("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/snake3D/snake/kula.obj", M, V, P);
//Model obj("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", M, V, P);
//Model obj3("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", newM3, V, P);

void initOpenGLProgram(GLFWwindow* window) {
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	std::vector<unsigned char> image[2];   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
							  //Wczytaj obrazek
	unsigned ejej = lodepng::decode(image[0], width, height, "grass.png");

	unsigned width2, height2;   //Zmienne do których wczytamy wymiary obrazka
								//Wczytaj obrazek
	unsigned ejej2 = lodepng::decode(image[1], width2, height2, "snake.png");

	glGenTextures(1, &tex[0]); //Zainicjuj dwa uchwyty
	glBindTexture(GL_TEXTURE_2D, tex[0]); //Uaktywnij uchwyt
										  //Wczytaj obrazek do pami?ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image[0].data());

	//W??cz bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex[1]); //Uaktywnij uchwyt
										  //Wczytaj obrazek do pami?ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width2, height2, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image[1].data());

	//W??cz bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
	apple.init("grass.png");
	snake.init("snake.png");

	M = glm::mat4(1.0f);
	V = lookAt(
		glm::vec3(0, 8, -16),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f);
	M2 = glm::translate(M2, glm::vec3(0.0f, 1.0f, 0.0f));
	apple.respawnInNewPlace(6);
	//M = glm::translate(M, glm::vec3(-1.0f, -1.0f, -1.0f));

	glfwSetKeyCallback(window, key_callback);
}
//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window) {	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));

	//glColor3d(0, 1, 0);
	//obj.drawModel();
	M = rotate(M, speed, glm::vec3(0.0f, 1.0f, 0.0f));
	M2 = rotate(M2, speed, glm::vec3(0.0f, 1.0f, 0.0f));
	M2 = glm::translate(M2, glm::vec3(0.01f, 0, 0));

	glBindTexture(GL_TEXTURE_2D, tex[0]); //Wybierz teksturę
	glEnableClientState(GL_VERTEX_ARRAY); //Włącz uzywanie tablicy współrzędnych wierzchołków
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //Włącz używanie tablicy współrzędnych teksturowania
	glVertexPointer(3, GL_FLOAT, 0, floorVertices); //Zdefiniuj tablicę, która jest źródłem współrzędnych wierzchołków
	glTexCoordPointer(2, GL_FLOAT, 0, floorTexCoords); //Zdefiniuj tablicę, która jest źródłem współrzędnych teksturowania
	glDrawArrays(GL_QUADS, 0, floorVertexCount); //Narysuj obiekt
	glDisableClientState(GL_VERTEX_ARRAY); //Wyłącz uzywanie tablicy współrzędnych wierzchołków
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Wyłącz używanie tablicy współrzędnych teksturowania
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M2));

	apple.draw(&V);
	snake.draw(&V);
	snake.move();
	glfwSwapBuffers(window);
}

int main(void)
{
	srand(time(NULL));
	GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1300, 760, "Snake", NULL, NULL); 
	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Zainicjuj bibliotekê GLEW		
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj¹ce

						 //G³ówna pêtla
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		drawScene(window); //Wykonaj procedurê rysuj¹c¹
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}

	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}