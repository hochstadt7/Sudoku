#ifndef BIGPROJECT_VALIDBOARD_H
#define BIGPROJECT_VALIDBOARD_H

#include "Board.h"

int is_valid(int **arr, int dimension, int row, int col, int value, int row_per_block, int col_per_block);
int in_row(const int *arr, int dimension, int value);
int in_col(int **arr, int dimension, int col, int value);
int in_block(int **arr, int block_start_row, int block_start_col, int value, int row_per_block, int col_per_block);
void fix_error(int **arr,int **error,int dimension,int row,int col,int value, int block_start_row, int block_start_col, int row_per_block,int col_per_block);
#endif /*BIGPROJECT_VALIDBOARD_H*/
