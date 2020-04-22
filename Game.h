#ifndef BIGPROJECT_GAME_H
#define BIGPROJECT_GAME_H

#include "Board.h"

void save(char *link,Board *board);/*Saves the current game board to the specified file, where X includes a full or relative path to the file*/
void set(int x, int y, int z, Board *b);/*Sets the value of cell <X,Y> to Z (X is the column, Y is the row)*/
void hint(int x, int y, Board *b);/*Give a hint to the user by showing the solution of a single cell X,Y*/
Board* edit(char *link, Board *old);/*Starts a puzzle in Edit mode, loaded from a file with the name "X", where X includes a full or relative path to the file*/
Board* solve(char *link, Board *old);/*Starts a puzzle in Solve mode, loaded from a file with the name "X", where X includes a full or relative path to the file*/
void setMarkErrors(int mark_errors, Board *b);
void guess(float threshold, Board *board);/*Guesses a solution to the current board using LP (not ILP!), with threshold X*/
void validate(Board *b);
void exit_game(Board *board);/*Terminates the program*/
#endif /*BIGPROJECT_GAME_H*/
