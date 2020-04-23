#ifndef BIGPROJECT_MAINAUX_H
#define BIGPROJECT_MAINAUX_H
#define DEBUG 0
/*the main-aux module contains useful lightweight functions that have frequent usage throughout the program*/

enum variableType {INT=1, INT_POINTER=2, DOUBLE=3}; /*possible variable types, used to initialize arrays with default values*/
int ping(int p); /*debugging conditioned print function*/
int** first_init(int dimension);/*initialize board*/
int** duplicateArray(int **arr, int dimension);/*creates and return a 2d array identical to the one provided*/
void copy_arrays(int **copy, int**paste,int dimension);/*copy data of copy to paste*/
int is_erroneous(int **error,int dimension);/*returns 1 if the pre-calculated error array provided contains any 1 values*/
void free_arrays(int **arr,int dimension);/*generic function to free an allocated 2d array*/
void *init_malloc(int size, int length, enum variableType type);/*allocates an array and assigns default values*/
void print_arr(int **arr,int dimension);/*prints a 2d array*/
#endif /*BIGPROJECT_MAINAUX_H*/
