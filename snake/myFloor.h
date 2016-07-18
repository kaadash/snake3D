#ifndef MYFLOOR_H
#define MYFLOOR_H

unsigned int floorVertexCount = 4;
unsigned int cubeVertexCount = 24;

float floorVertices[] = {
	-5,0,-5,
	5,0,-5,
	5,0,5,
	-5,0,5
};

float floorColors[] = {
	1,1,0, 1,1,0, 1,1,0, 1,1,0,
};

float floorTexCoords[] = {
	0,0, 1,0, 1,1, 0,1,
};

float cubeVertices[] {
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

#endif