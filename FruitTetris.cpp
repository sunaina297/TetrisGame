

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include "headers/backboard.h"
#include "helper.h"
#include "play.h"




using namespace std;

void winReshapeFcn(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	init();

	glutDisplayFunc(createBoard);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(Normalkeyboard);
	glutIdleFunc(createBoard);
	//glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	errorGL();
}
