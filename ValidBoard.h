#ifndef BIGPROJECT_VALIDBOARD_H
#define BIGPROJECT_VALIDBOARD_H

#include "Board.h"
/*the valid board module contains functions pertaining to the validity of some cell assignment*/
/*checks that and assignment of [value] to cel [row][col] of board [arr] is valid*/
int is_valid(int **arr, int dimension, int row, int col, int value, int row_per_block, int col_per_block);
/*checks if [value] already exists in [arr], which contains a single board row*/
int in_row(const int *arr, int dimension, int value);
/*checks if [value] already exists in [arr] at column [col]*/
int in_col(int **arr, int dimension, int col, int value);
/*checks if [value] already exists in [arr] at the block starting at [block_start_row]*/
int in_block(int **arr, int block_start_row, int block_start_col, int value, int row_per_block, int col_per_block);
/*sets error flags as necessary*/
void fix_error(int **arr,int **error,int dimension,int row,int col,int value, int block_start_row, int block_start_col, int row_per_block,int col_per_block);
/*recalculates the error board*/
void reCalcErrors(Board *b);
#endif /*BIGPROJECT_VALIDBOARD_H*/
