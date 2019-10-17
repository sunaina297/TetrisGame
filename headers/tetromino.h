
#include <GL/glut.h>
#pragma once
#ifndef _tetromino_h
#define _tetromino_h

struct tetromino_result {
	int id_list;
	vertex2* last_coords;
	int* last_coord_pts;
};

tetromino_result drop_tetromino(bool** curr_tetro, int tile_x, vertex2* arr, int curr_y, vertex3* colr);

savedtetro* saved_tetromino(int* lst, vertex3* colr, savedtetro* s, int num);


int saved_display(savedtetro* s, int num, vertex2* arr);

int collision(int* pt, savedtetro* s, int num);

bool* corner_collision(int* pt, int tile);

bool game_over(int* pt, int num, savedtetro* s);


#endif