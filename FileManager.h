#ifndef BIGPROJECT_FILEMANAGER_H
#define BIGPROJECT_FILEMANAGER_H

/*the file manager module contains functions related to the loading and saving of board to files*/

Board* load(char *link, enum gameMode mode);/*load board game from a file*/
int is_ok(const char *fix);/*valid input of cell*/
Board* un_format(FILE *dest);/*error message of loading file failure*/

#endif /*BIGPROJECT_FILEMANAGER_H*/
