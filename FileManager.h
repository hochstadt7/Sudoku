#ifndef BIGPROJECT_FILEMANAGER_H
#define BIGPROJECT_FILEMANAGER_H

Board* load(char *link, enum gameMode mode);/*load board game from a file*/
int is_ok(const char *fix);/*valid input of cell*/
int there_are_x_empty(int **arr, int dimension, int x);
Board* un_format(FILE *dest);/*error message of loading file failure*/


#endif /*BIGPROJECT_FILEMANAGER_H*/
