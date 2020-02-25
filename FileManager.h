//
// Created by LENOVO on 08/01/2020.
//

#ifndef BIGPROJECT_FILEMANAGER_H
#define BIGPROJECT_FILEMANAGER_H

Board* load(char *link);/*load board game from a file*/
int is_ok(const char *fix);/*valid input of cell*/
Board* un_format(FILE *dest);/*error message of loading file failure*/

#endif //BIGPROJECT_FILEMANAGER_H
