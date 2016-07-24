#ifndef MAIN_H
#define MAIN_H
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Model.h"
#include "Constants.h"
#include "lodepng.h"
#include "Food.h"
#include "Snake.h"
#include "GameBoard.h"
#include "myFloor.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

GLuint tex[2];
glm::mat4 V, V1, M = glm::mat4(1.0f), P;

#endif