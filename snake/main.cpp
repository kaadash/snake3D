﻿#include "main.h"

//Uchwyty na shadery
ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.

							  //Uchwyty na VAO i bufory wierzchołków
GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint bufColors;  //Uchwyt na bufor VBO przechowujący tablicę kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowujący tablickę wektorów normalnych

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

bool check_time() {
	new_time = clock();
	if (new_time - start_time > speed) {
		start_time = new_time;
		return true;
	}
	return false;
}

void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			gameBoard.rotate(rotateStep);
			snake.relativeRotate(gameBoard.getM(), rotateStep);
			apple.relativeRotate(gameBoard.getM(), rotateStep);
		}
		if (key == GLFW_KEY_RIGHT) {
			gameBoard.rotate(-rotateStep);
			snake.relativeRotate(gameBoard.getM(), -rotateStep);
			apple.relativeRotate(gameBoard.getM(), -rotateStep);
		}
		if (key == GLFW_KEY_A) {
			if (snake.getTurn() == 0) {
				snake.turnLeft();
			}
		}
		if (key == GLFW_KEY_D) {
			if (snake.getTurn() == 0) {
				snake.turnRight();
			}
		}
		if (key == GLFW_KEY_EQUAL) zoom -= 0.5;
		if (key == GLFW_KEY_MINUS) zoom += 0.5;
		if (key == GLFW_KEY_W) {
			if (speed != 100) speed -= 100;
		}
		if (key == GLFW_KEY_S) speed += 100;
	}

	//if (action == GLFW_RELEASE) {
	//	speed = 0;
	//}
}

//glm::mat4 newM3 = glm::mat4(1.0f);
//Model obj("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/snake3D/snake/kula.obj", M, V, P);
//Model obj("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", M, V, P);
//Model obj3("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", newM3, V, P);


//Tworzy bufor VBO z tablicy
GLuint makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który będzie zawierał tablicę danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicę do VBO

	return handle;
}

//Przypisuje bufor VBO do atrybutu 
void assignVBOtoAttribute(ShaderProgram *shaderProgram, char* attributeName, GLuint bufVBO, int vertexSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //Włącz używanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, vertexSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location mają być brane z aktywnego VBO
}

void initOpenGLProgram(GLFWwindow* window) {
	
	//glEnable(GL_LIGHTING);

	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt"); //Wczytaj program cieniujący 


	//*****Przygotowanie do rysowania pojedynczego obiektu*******
	//Zbuduj VBO z danymi obiektu do narysowania
	bufVertices = makeBuffer(cubeVertices, cubeVertexCount, sizeof(float) * 4); //VBO ze współrzędnymi wierzchołków
	bufColors = makeBuffer(colors, cubeVertexCount, sizeof(float) * 4);//VBO z kolorami wierzchołków
	bufNormals = makeBuffer(normals, cubeVertexCount, sizeof(float) * 4);//VBO z wektorami normalnymi wierzchołków

																	 //Zbuduj VAO wiążący atrybuty z konkretnymi VBO
	glGenVertexArrays(1, &vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

	glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO

	assignVBOtoAttribute(shaderProgram, "vertex", bufVertices, 4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "color", bufColors, 4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute(shaderProgram, "normal", bufNormals, 4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze

	glBindVertexArray(0); //Dezaktywuj VAO


	// włączenie testu bufora głębokości
	glEnable(GL_DEPTH_TEST);
	
	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	gameBoard.init("grass.png");
	apple.init("apple.png");
	snake.init("snake.png");
	snake.setInitPosition(0, 1, 0);

	M = glm::mat4(1.0f);
	
	P = glm::perspective(50 * PI / 180, 1.0f, 1.0f, 50.0f);

	std::vector<Coordinate> coordinates;
	for (auto &snakePart : snake.getSnakeParts()) {
		coordinates.push_back(snakePart.getCurrentPosition2());
	}

	apple.respawnInNewPlace(4, &gameBoard, coordinates);
	glfwSetKeyCallback(window, key_callback);
}
//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window) {	
	if (gameBoard.isLoose()) {
		string tmp;
		sprintf_s((char*)tmp.c_str(),sizeof((char*)tmp.c_str()),  "%d", gameBoard.getPoints());
		string str = tmp.c_str();
		
		std::stringstream ss;
		ss << "Przegrales!\nZdobyles " << str << " punktow.";
		MessageBoxA(NULL, ss.str().c_str(), "PRZEGRANA", MB_OK);
		exit(EXIT_SUCCESS);
	}

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	V = lookAt(
		glm::vec3(0, zoom, -2*zoom),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));
	
	//gameBoard.draw(vao, shaderProgram, &V, &M, &P, floorVertices, floorTexCoords, floorVertexCount);
	apple.draw(vao, shaderProgram, &V, &M, &P, cubeVertices, cubeTexCoords, cubeVertexCount);
	snake.draw(vao, shaderProgram, &V, &M, &P, cubeVertices, cubeTexCoords, cubeVertexCount);
	if (check_time()) {
		snake.move(&gameBoard, &apple);
	}
	
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