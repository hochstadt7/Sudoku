

#ifndef BIGPROJECT_GAME_H
#define BIGPROJECT_GAME_H

#include "Board.h"
//#include "History.h"
void save(char *link,Board *board);/*save board game to the link specified*/
void set(int **arr,int **error, int dimension, int **fixed, int y, int x, int z, int row_per_block, int col_per_block,List *lst);/*set value to cell specified*/
void mark_errors(int mark,Board *board);/*mark invalid cells*/
void hint(int **arr,int **fixed,int **solution,int **error, int dimension,int y, int x);/*hint for appropriate value of cell*/
void autofill(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block,List *lst);/* fill cells with only one legal value*/
Board* edit(char *link,Board *old);
#endif //BIGPROJECT_GAME_H
