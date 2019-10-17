#include <GL/glut.h>
#pragma once
#ifndef _helper_h
#define _helper_h


GLfloat* change_color(void);

int set_random_tile(void);

GLenum errorGL(void);

bool** set_random_tetris_block(void);

bool** helper_rotate(bool** tetro_curr);


#endif