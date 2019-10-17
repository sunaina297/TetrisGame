#include <GL/glut.h>
#pragma once
#ifndef _constants_h
#define _constants_h


//counterclockwise rendering 
const int topL[] = { 20, 220 };
const int topR[] = { 120, 220 };
const int bottomL[] = { 20, 20 };
const int bottomR[] = { 120, 20 };

const int left_edge = topL[0];
const int right_edge = topR[0];
const int top_edge = topL[1];
const int bottom_edge = bottomL[1];

//values for the grid
const int Rows = 20;
const int Cols = 10;
const int squareSZ = 10;
const int vertexes_per_line = 4 * Cols; // 40 in ours


// define all vertices
typedef GLint vertex2[2];

typedef GLfloat vertex3[3];

typedef GLfloat savedtetro[4];


const bool tetro[20][4] = {
	{0, 0, 0, 0},
	{1 ,1 ,1 ,1},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0},
	{0 ,0 ,1 ,1},
	{0, 1, 1, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0},
	{0 ,1 ,1 ,1},
	{0, 1, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0},
	{0 ,1 ,1 ,1},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
};



#endif
