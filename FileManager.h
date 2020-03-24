//
// Created by LENOVO on 08/01/2020.
//

#ifndef BIGPROJECT_FILEMANAGER_H
#define BIGPROJECT_FILEMANAGER_H

Board* load(char *link, enum status mode);/*load board game from a file*/
int is_ok(const char *fix);/*valid input of cell*/
Board* un_format(FILE *dest);/*error message of loading file failure*/
void free_arrays(int **arr,int dimension);/*free arrays*/

#endif //BIGPROJECT_FILEMANAGER_H
