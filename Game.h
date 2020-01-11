

#ifndef BIGPROJECT_GAME_H
#define BIGPROJECT_GAME_H

#include "Board.h"
#include "History.h"
void save(char *link,Board *board);
void set(int **arr,int **error, int dimension, int **fixed, int y, int x, int z, int row_per_block, int col_per_block,List *lst);
void mark_errors(int mark,Board *board);
void hint(int **solution, int y, int x);
void autofill(int **arr,int dimension,int row_per_block,int col_per_block);
#endif //BIGPROJECT_GAME_H
