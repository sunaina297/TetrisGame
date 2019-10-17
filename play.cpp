
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/backboard.h"
#include "headers/const.h"
#include "headers/tetromino.h"
#include "helper.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;



void keyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		move_left();
		break;
	case GLUT_KEY_RIGHT:
		move_right();
		break;
	case GLUT_KEY_UP:
		rotate();
		break;
	case GLUT_KEY_DOWN:
		slow();
		break;
	}
		return;
}


void Normalkeyboard(unsigned char key, int x, int y) {
	if (key == 'r')
	{
		game_end();
		glutPostRedisplay();
	}
	else if (key == 'q')
	{
		exit(1);
	}
}
