
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "headers/backboard.h"
#include "headers/const.h"
#include "headers/tetromino.h"
#include "helper.h"
#include "play.h"
#include <chrono>

using namespace std;

//---------  VARIABLES ------------------
// for vertices + colors (dropping and stacked)
static vertex2 points[Rows * Cols * 4] = { 0 };  //800 points
vertex3 colors[4] = { 1 };
int NUM_DROPPED_TILES = 0;
savedtetro* save;
int tile_x=0;

// for trtromino drop execution + inits
tetromino_result response;
int* stop_points;
bool** curr_tetro_block;
int game = 0;
int bottom_hit;
int curr_y;
int bottom_blocks_id;
int collision_val;
int check_update;

// for drop timer
int sleep_time=300;
auto start = std::chrono::steady_clock::now();
auto updated = std::chrono::steady_clock::now();
auto elapsed = 10;



// --------- FUNCTIONS -------------------

// ------ INITS -----------
// create the vertices pointer
static void vertexes() {
	// save vertexes in an array
	int ind = 0; //+=6
	for (int r = bottomL[1]; r < topR[1]; r += 10) {
		for (int c = bottomL[0]; c < topR[0]; c += 10) {

			//square
			points[ind][0] = c;
			points[ind][1] = r;

			points[ind + 1][0] = c + 10;
			points[ind + 1][1] = r;

			points[ind + 2][0] = c + 10;
			points[ind + 2][1] = r + 10;

			points[ind + 3][0] = c;
			points[ind + 3][1] = r + 10;

			ind += 4;

		}


	}
}



void init(void) {

	//saving squares vertices
	vertexes();
	save = new savedtetro[4];

	// initialize for new tetromino
	tile_x = set_random_tile();
	curr_tetro_block = set_random_tetris_block();
	int bottom_hit = top_edge - (squareSZ);
	int curr_y = top_edge;
	response.id_list = 0;
	response.last_coord_pts = new int[4];
	response.last_coord_pts = { 0 };

	bottom_blocks_id = saved_display(save, NUM_DROPPED_TILES, points);
	collision_val = 0;
	check_update = 0;

	//display window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(400, 20);
	glutInitWindowSize(500, 600);
	glutCreateWindow("Tetris Game");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 180.0, 0.0, 250.0);
}



// keypress functions
int move_x_val_l = 0;
int move_x_val_r = 0;
void move_right(void) {
	if (move_x_val_r != 1) {
		tile_x += squareSZ;
		move_x_val_l = 0;
	}
}
void move_left(void) {

	if (move_x_val_l != 1) {
		tile_x -= squareSZ;
		move_x_val_r = 0;
	}
}
void slow(void) {
	if (sleep_time -50 > 0) {
		sleep_time -= 50;
	}
}
void rotate(void) {
	curr_tetro_block = helper_rotate(curr_tetro_block);
}


// --------- RESETS -------------
// for reset of falling tetro
void reset_tetro() {
	tile_x = set_random_tile();
	curr_tetro_block = set_random_tetris_block();
	bottom_hit = top_edge - (squareSZ);
	curr_y = top_edge;

	response.id_list = 0;
	response.last_coord_pts = new int[4];
	response.last_coord_pts = { 0 };

	bottom_blocks_id = saved_display(save, NUM_DROPPED_TILES, points);
	collision_val = 0;
	check_update = 0;

	// color set-up
	for (int i = 0; i < 4; i++) {
		GLfloat* colr = change_color();
		colors[i][0] = colr[0];
		colors[i][1] = colr[1];
		colors[i][2] = colr[2];
	}

	move_x_val_l = 0;
	move_x_val_r = 0;
	collision_val = 0;
	sleep_time = 300;
	start = std::chrono::steady_clock::now();
}


// for replay
void game_end(void) {
	printf("new game..\n");


	save = new savedtetro[4];
	NUM_DROPPED_TILES = 0;

	reset_tetro();
}




// ---------- GAME !! ---------------
// loop for the diaplay of game
int tetris_loop( int tile_x, bool** curr_tetro_block, int bottom_hit,
					int curr_y, int bottom_blocks_id, int collision_val) {

	// create the background grid
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, points);
	glutSpecialFunc(keyboard);

	// drop tetro
	response = drop_tetromino(curr_tetro_block, tile_x, points, curr_y, colors);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCallList(response.id_list);

	//check if new updates is touching any edges
	bool* move_x_val = corner_collision(response.last_coord_pts, tile_x);
	if (move_x_val[0] != 0) {  //left edge
		move_x_val_l = 1;
	}
	if (move_x_val[1] != 0) {   //right edge
		move_x_val_r = 1;
	}
;

	// stacked tetromino -- static
	if (bottom_blocks_id != 0) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glCallList(bottom_blocks_id);
	}

	// grid -- static
	glColor3f(0.3, 0.30, 0.3);
	glPolygonMode(GL_FRONT, GL_LINE);
	glDrawArrays(GL_QUADS, 0, 800);

	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();

	glutSwapBuffers();

	return 1;
}




void createBoard(void) {
	game = game_over(response.last_coord_pts, NUM_DROPPED_TILES, save);
	if (!game) {
		start = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(start - updated).count();

		// main -- for background + drop
		//printf("move x: %d\n", move_x_val);

		if (elapsed > sleep_time) {
			;
			check_update = tetris_loop(tile_x, curr_tetro_block, bottom_hit,
				curr_y, bottom_blocks_id, collision_val);
			curr_y -= squareSZ;
			updated = std::chrono::steady_clock::now();
		}


		// check for collision
		// if the last_coordinates have points in the saved_points,
		// then it has collided with another tetromino
		if (check_update == 1) {
			collision_val = collision(response.last_coord_pts, save, NUM_DROPPED_TILES);
			check_update = 0;
		}

		// tile has stopped -- stack it
		if (collision_val == 1) {
			NUM_DROPPED_TILES += 1;
			stop_points = response.last_coord_pts;
			save = saved_tetromino(stop_points, colors, save, NUM_DROPPED_TILES);
			reset_tetro();
		}

		// check stacked for consecutive fruits


	}


}
