#ifndef BIGPROJECT_MAINAUX_H
#define BIGPROJECT_MAINAUX_H
#define DEBUG 1

enum variableType {INT=1, INT_POINTER=2, DOUBLE=3};
int ping(int p);
int** first_init(int dimension);/*initialize board*/
int** duplicateArray(int **arr, int dimension);
void copy_arrays(int **copy, int**paste,int dimension);/*copy data of copy to paste*/
int is_erroneous(int **error,int dimension);
void free_arrays(int **arr,int dimension);
void *init_malloc(int size, int length, enum variableType type);
void print_arr(int **arr,int dimension);
#endif /*BIGPROJECT_MAINAUX_H*/
