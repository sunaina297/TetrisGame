
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



// drop down tile, return coordinates of last position
tetromino_result drop_tetromino(bool** curr_tetro, int tile_x, vertex2* arr, int curr_y, vertex3* colr) {

	int id_1 = glGenLists(1);
	int increase_1 = 0;

	// coordinates for last position
	// 4 tiles = 2*4
	vertex2* last_coords_arr;
	last_coords_arr = new vertex2[8];
	int last_coord_index = 0;
	int* tile_points;
	tile_points = new int [4];
	//printf("test x: %d\n", tile_x);
	glNewList(id_1, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	// tiles rendering

	for (int bool_bottom = 0; bool_bottom < 4; bool_bottom += 1) {
		int coord_y = curr_y - (bool_bottom * squareSZ);
		for (int bool_right = 0; bool_right < 4; bool_right += 1) {
			if (curr_tetro[bool_bottom][bool_right]) {
				int coord_x = tile_x + (bool_right * squareSZ);
				int tile_point = ((((coord_y - bottom_edge) / squareSZ) - 1) * 40) + (((coord_x - left_edge) / squareSZ) * 4);
				if (tile_point > 800) {
					printf("Error with tile_point %d.\n", tile_point);
				}
				//printf("tile point: %d\n", tile_point);
				// save coordinates
				last_coords_arr[last_coord_index][0] = arr[tile_point][0];
				last_coords_arr[last_coord_index][1] = arr[tile_point][1];
				last_coords_arr[last_coord_index + 1][0] = arr[tile_point + 2][0];
				last_coords_arr[last_coord_index + 1][1] = arr[tile_point + 2][1];

				tile_points[increase_1] = tile_point;


				//draw the square tile
				glColor3fv(colr[increase_1]);
				//printf(" test: %f %f %f\n", colr[color_per_tile][0], colr[color_per_tile][1], colr[color_per_tile][2]);
				glRecti(arr[tile_point][0], arr[tile_point][1], arr[tile_point + 2][0], arr[tile_point + 2][1]);
				//glColor3f(0.0, 1.0, 0.0);
				last_coord_index += 2;
				increase_1 += 1;
				//printf("clor tile # %d\n", color_per_tile);

			}
		}
	}
	glEndList();

	/*for (int i = 00; i < 8; i++) {
		printf("last coords: %d %d\n", last_coords_arr[i][0], last_coords_arr[i][1]);
	}*/

tetromino_result result;
result.id_list = id_1;
result.last_coords = last_coords_arr;
result.last_coord_pts = tile_points;
//printf("stop");
return result;
}


// add to array of saved tetromino and colors
savedtetro* saved_tetromino(int* lst, vertex3* colr, savedtetro* s, int num) {

	int sz_saved = 4 * (num);
	savedtetro* new_saved = new savedtetro[sz_saved];
	//new_saved = { 0 };
	int sz_color_val = 3;
	int index = 0;

	printf(" sz: %d\n", sz_saved);
	printf(" point: %d %d %d %d\n", lst[0], lst[1], lst[2], lst[3]);
	//printf(" color: %f %f %f \n", colr[1][0], colr[1][1], colr[1][2]);

	for (int i = 0; i < sz_saved; i++) {

		if (i < sz_saved - 4) {
			// copy old stuff over
			// copy old stuff over
			new_saved[i][0] = s[i][0];
			new_saved[i][1] = s[i][1];
			new_saved[i][2] = s[i][2];
			new_saved[i][3] = s[i][2];
			//printf("old saved: point %f, colr: %f %f %f\n", new_saved[i][0], new_saved[i][1], new_saved[i][2], new_saved[i][3]);
		}
		else {
			// add
			new_saved[i][0] = lst[index];  // save point
			new_saved[i][1] = colr[index][0];
			new_saved[i][2] = colr[index][1];
			new_saved[i][3] = colr[index][2];
			index += 1;
			//printf("new saved: point %f, colr: %f %f %f\n", new_saved[i][0], new_saved[i][1], new_saved[i][2], new_saved[i][3]);
		}
	}

	delete[] s;
	return new_saved;
}


// receive an 4v array with 1 points and 3 vals for colors of that point
int saved_display(savedtetro* s, int num, vertex2* arr) {
	int len = num * 4;
	int id_2 = glGenLists(1);
if (num == 0) {
	return 0;
}
glNewList(id_2, GL_COMPILE);
glPolygonMode(GL_FRONT, GL_FILL);
// set up while loop for all stacked tiles
for (int i = 0; i < len; i++) {

	//draw the square tile
	glColor3f(s[i][1], s[i][2], s[i][3]);
	//printf(" test: %f %f %f\n", colr[color_per_tile][0], colr[color_per_tile][1], colr[color_per_tile][2]);
	int pt = s[i][0];
	glRecti(arr[pt][0], arr[pt][1], arr[pt + 2][0], arr[pt + 2][1]);
	//glColor3f(0.0, 1.0, 0.0);

}

glEndList();

return id_2;
}


bool check_if_saved(int val, savedtetro* s, int num) {
	int sz = num * 4;
	int index = sz;
	bool flag = 0;

	while (flag == 0 && index > 0) {
		if (s[index][0] == val) {
			flag = 1;
		}
		index -= 1;
	}

	return flag;
}


bool* corner_collision(int* pt, int tile) {
	bool* flag;
	flag = new bool[2];
	flag[0] = 0;
	flag[1] = 0;
	if (pt != NULL) {
		for (int i = 0; i < 4; i++) {
			//printf(" test %d \n", pt[i]);
			// check for all left_edge points
			if ((pt[i] % vertexes_per_line) == 0) {
				printf("pointleft %d\n", pt[i]);
				flag[0] = 1;
				printf("flagl %d\n", flag[0]);
			}
			if (((pt[i] + 4) % vertexes_per_line) == 0) {
				printf("pointright %d\n", pt[i]);
				flag[1] = 1;
				printf("flag r %d\n", flag[1]);
			}
		}
	}
	//printf("test flag: %d %d\n", flag[0], flag[1]);
	return flag;
}


// check curret tetromino points
// if any of its points are already saved then it has hit another tetromino
// check for corners -- corner points are collision
// # of tiles per tetro is 4
int collision(int* pt, savedtetro* s, int num) {
	bool flag = 0;
	int pt_index = 0;
	int vertex_increase = 40;

	//printf(" %d", pt[0]);
	//corners
	for (int i = 0; i < 4; i++) {
		// if the vertex has reached the bottom
		if (pt[i] < 40) {
			//printf(" 40< collide at %d\n", pt[i]);
			flag = 1;
		}
	}

	while (flag == 0 && pt_index < 4) {
		// bottom tile pt
		int below_pt = pt[pt_index] - vertex_increase;
		flag = check_if_saved(below_pt, s, num);
		pt_index += 1;
	}

	return flag;
}


bool game_over(int* pt, int num, savedtetro* s) {
	bool over = 0;
	int sz_saved = 4 * (num);
	int index = sz_saved - 1;
	while (index > 0) {
		if (s[index][0] >= 720){
		over = 1;
		}
		index -= 1;
	}
	if (over == 1) {
		delete[] s;
	}
	return over;
}
