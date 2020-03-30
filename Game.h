

#ifndef BIGPROJECT_GAME_H
#define BIGPROJECT_GAME_H

#include "Board.h"

void save(char *link,Board *board);/*Saves the current game board to the specified file, where X includes a full or relative path to the file*/
void set(int **arr,int **error, int dimension, int **fixed, int y, int x, int z, int row_per_block, int col_per_block,List *lst);/*Sets the value of cell <X,Y> to Z (X is the column, Y is the row)*/
void mark_errors(int mark,Board *board);/*mark invalid cells*/
void hint(int **arr,int **fixed,int **solution,int **error, int dimension,int y, int x);/*Give a hint to the user by showing the solution of a single cell X,Y*/
void autofill(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block,List *lst);/*Automatically fill "obvious" values – cells which contain a single legal value*/
Board* edit(char *link,Board *old, enum status mode);/*Starts a puzzle in Edit mode, loaded from a file with the name "X", where X includes a full or relative path to the file*/
void exit_game(Board *board);/*Terminates the program*/
Board* solve(char *link,Board *old, enum status mode);/*Starts a puzzle in Solve mode, loaded from a file with the name "X", where X includes a full or relative path to the file*/
void guess(int x,int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block);/*Guesses a solution to the current board using LP (not ILP!), with threshold X*/
#endif //BIGPROJECT_GAME_H
