#ifndef BIGPROJECT_GENERATE_H
#define BIGPROJECT_GENERATE_H
#include "Board.h"
void generate(int x, int y, Board *b);
int fill_x_cells(Board *b, int x);
int keep_y_cells(Board *b, int y);
int there_are_x_empty(int **arr, int dimension, int x);
#endif /*BIGPROJECT_GENERATE_H*/
