#include "main.h"
float speed = 0;
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed = -3.14f;
		if (key == GLFW_KEY_RIGHT) speed = 3.14f;
	}

	if (action == GLFW_RELEASE) {
		speed = 0;
	}
}
glm::mat4 newM = glm::mat4(1.0f);
glm::mat4 newM2 = glm::mat4(1.0f);

glm::mat4 newM3 = glm::mat4(1.0f);
Model obj("D:/Prace/grafika/ogl-master/ogl-master/tutorial07_model_loading/cube.obj", newM, V, P);
Model obj2("D:/Prace/grafika/ogl-master/ogl-master/tutorial07_model_loading/cube.obj", newM2, V, P);
Model obj3("D:/Prace/grafika/ogl-master/ogl-master/tutorial07_model_loading/cube.obj", newM3, V, P);

void initOpenGLProgram(GLFWwindow* window) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//************Tutaj umieszczaj kod, kt�ry nale�y wykona� raz, na pocz�tku programu************
	M = glm::mat4(1.0f);
	V = lookAt(
		glm::vec3(10, 20, -5),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 100, 0)
	);
	P = glm::perspective(60 * PI / 180, 1.0f, 1.0f, 50.0f);
	newM = glm::translate(newM, glm::vec3(1.0f, 1.0f, 1.0f));
	newM2 = glm::translate(newM2, glm::vec3(-1.0f, -1.0f, -1.0f));

	glfwSetKeyCallback(window, key_callback);
}
//Procedura rysuj�ca zawarto�� sceny
void drawScene(GLFWwindow* window) {
	glClearColor(1, 0.2, 0.7, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(V*M));
	newM2 = rotate(newM2, 0.01f, glm::vec3(1, 0, 0));
	newM = glm::translate(newM, glm::vec3(0.01f, 0.01f, 0.01f));
	obj.drawModel();
	obj2.drawModel();
	obj3.drawModel();
	glfwSwapBuffers(window);
}

int main(void)
{
	srand(time(NULL));
	GLFWwindow* window; //Wska�nik na obiekt reprezentuj�cy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedur� obs�ugi b��d�w

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL. 

	if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
	glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Zainicjuj bibliotek� GLEW		
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj�ce

						 //G��wna p�tla
	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		drawScene(window); //Wykonaj procedur� rysuj�c�
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
	}

	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}