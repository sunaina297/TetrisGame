
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "headers/backboard.h"
#include "headers/const.h"
#include "headers/tetromino.h"
#include <string>
#include <vector>



GLfloat* change_color(void) {
	GLfloat* rand_color;
	rand_color = new GLfloat [3];
	int num = rand() % 5;

	if (num == 0) {
		//glColor3f(0.1, 1.0, 0.3);
		rand_color[0] = 0.1;
		rand_color[1] = 1.0;
		rand_color[2] = 0.3;
	}
	else if (num == 1) {
		//glColor3f(1.0, 0.30, 0.3);
		rand_color[0] = 1.0;
		rand_color[1] = 0.3;
		rand_color[2] = 0.3;
	}
	else if (num == 2) {
		//glColor3f(0.0, 0.30, 0.9);
		rand_color[0] = 0.0;
		rand_color[1] = 0.3;
		rand_color[2] = 0.9;;
	}
	else if (num == 3) {
		//glColor3f(0.7, 0.70, 0.3);
		rand_color[0] = 0.7;
		rand_color[1] = 0.7;
		rand_color[2] = 0.3;
	}
	else if (num == 4) {
		//glColor3f(0.8, 0.4, 0.3);
		rand_color[0] = 0.8;
		rand_color[1] = 0.4;
		rand_color[2] = 0.3;
	}


	//printf(" original works: %f %f %f\n", rand_color[0], rand_color[1], rand_color[2]);

	return rand_color;
}


// random tile vertex will be an x coord value
int set_random_tile(void) {
	srand(time(NULL));
	int var_to_avoid_right_edge = right_edge - 4 * squareSZ;
	int random_tile_begin = rand() % (right_edge);
	//printf(" 1st tile rnd %d\n", random_tile_begin);
	// set edge cases
	if (random_tile_begin < left_edge) {
		random_tile_begin = left_edge;
		//printf(" left tile rnd %d\n", random_tile_begin);
	}
	else if (random_tile_begin > var_to_avoid_right_edge) {
		random_tile_begin = var_to_avoid_right_edge;
	}

	// set case for within boundary
	// random var could be non-vertex points -- make them vertexes
	while ((random_tile_begin % squareSZ) != 0) {
		random_tile_begin -= 1;
	}
	//printf("tile rnd %d\n", random_tile_begin);

	return random_tile_begin;

}



bool** set_random_tetris_block(void) {
	srand(time(NULL));
	bool** tetro_block = 0;
	tetro_block = new bool* [4];
	int tetris_random_index[4] = { 0,4,8,12 };
	int rand_tetris_index = rand() % 3;
	int index = tetris_random_index[rand_tetris_index];

	for (int i = 0; i < 4; i += 1) {
		tetro_block[i] = new bool [4];
		for (int j = 0; j < 4; j += 1) {
			tetro_block[i][j] = tetro[index][j];
			//printf("treo bool %d %d", i, j);
		}
		index += 1;
	}
	return tetro_block;
}


bool** helper_rotate(bool** tetro_curr) {
	bool** tetro_block = 0;
	tetro_block = new bool* [4];
	//init
	for (int i = 0; i < 4; i += 1) {
		tetro_block[i] = new bool[4];
		for (int j = 0; j < 4; j += 1) {
			tetro_block[i][j] = 0;
			//printf("treo bool %d %d", i, j);
		}
	}



	// reotate tetro block
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tetro_block[j][i] = tetro_curr[i-1][3-j];
			printf("new block: %d\n", tetro_block[j][i]);
		}

	}

	//cant set in loop
	tetro_block[0][0] = tetro_curr[3][3];
	tetro_block[1][0] = tetro_curr[3][2];
	tetro_block[2][0] = tetro_curr[3][1];
	tetro_block[3][0] = tetro_curr[3][0];

	return tetro_block;

}






GLenum errorGL(void) {
	GLenum code;
	const GLubyte* err;

	code = glGetError();
	err = gluErrorString(code);
	fprintf(stderr, "OpenGL error: %s\n", err);
	return code;
}
