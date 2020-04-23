#ifndef BIGPROJECT_GENERATE_H
#define BIGPROJECT_GENERATE_H
#include "Board.h"
void generate(int x, int y, Board *b); /*generate a new board configuration by setting x new values,
 * finding a possible solution with ILP, and keeping all but y of the remaining values*/
int fill_x_cells(Board *b, int x);/*find and assign values to x previously empty cells*/
int keep_y_cells(Board *b, int y);/*unset all but y cells*/
int there_are_x_empty(int **arr, int dimension, int x);/*checks how many empty values exist*/
#endif /*BIGPROJECT_GENERATE_H*/
