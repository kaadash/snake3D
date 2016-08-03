#include "main.h"

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

//Model obj("Jabko8.obj", M, V, P);
//Model obj("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", M, V, P);
//Model obj3("C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ogl/tutorial07_model_loading/cube.obj", newM3, V, P);

void initOpenGLProgram(GLFWwindow* window) {
	glEnable(GL_LIGHTING); 
	
	glEnable(GL_LIGHT0);
	GLfloat light1_ambient[] = { 1, 1, 1, 1.0 };
	GLfloat light1_diffuse[] = { 0.2, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 10);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHT1);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1, 0.2, 0.6);

	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	glGenTextures(4, &tex[0]); //Zainicjuj dwa uchwyty
	
	gameBoard.init2("grass.png", "Podloga2.obj");
	apple.init2("jabkotextura.png", "Jabko8.obj"); // to sie nie zmienia
	snake.init("snake.png", "KostkaRosolowa2.obj");
	snake.setInitPosition(0, 1, 0);

	M = glm::mat4(1.0f);
	V = lookAt(
		glm::vec3(0, zoom, -2 * zoom),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
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
	V = lookAt(
		glm::vec3(0, zoom, -2 * zoom),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(value_ptr(V**gameBoard.getM()));

	gameBoard.draw2(&V);
	

	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(value_ptr(V**apple.getM()));

	apple.draw2(&V);


	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(value_ptr(V*M2));

	snake.draw(&V);


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