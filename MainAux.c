#include <stdio.h>
#include <stdlib.h>
#include "MainAux.h"

/*the main-aux module contains useful lightweight functions that have frequent usage throughout the program*/
/*ping function used for debugging*/

int ping(int p){
#if DEBUG
    printf("ping %d\n", p);
#endif
    return p;
}

/*initialize the array*/
int** first_init(int dimension) {
    int i,j;
    int **arr=(int **) calloc(dimension , sizeof(int *));
    if(!arr)
    {
        printf("first_init failed.\n");
        return NULL;
    }
    for (i = 0; i < dimension; i++) {
        arr[i] = (int *) calloc(dimension , sizeof(int));
        if (!arr[i] ) {
            for(j=0; j<i; j++) {
                free(arr[j]);
            }
            free(arr);
            printf("first_init failed.\n");
            return NULL;
        }
    }
    return arr;
}
/*free array resources*/
void free_arrays(int **arr,int dimension){
    int index;
    for(index=0; index<dimension; index++) {
        free(arr[index]);
    }
    free(arr);
}
/*moves over values from one 2d array to another*/
void copy_arrays(int **copy, int **paste,int dimension)
{
    int index_row,index_col;
    for(index_row=0; index_row<dimension; index_row++){
        for(index_col=0; index_col<dimension; index_col++)
        {
            paste[index_row][index_col]=copy[index_row][index_col];
        }
    }
}
/*returns a 2d array identical to the one provided */
int** duplicateArray(int **arr, int dimension)
{
    int **copy = first_init(dimension);
    copy_arrays(arr, copy, dimension);
    return copy;
}
/*find whether the board is erroneous*/
int is_erroneous(int **error,int dimension){
    int row,col;
    for(row=0; row<dimension; row++){
        for(col=0; col<dimension; col++){
            if(error[row][col]==1)
                return 1;
        }
    }
    return 0;
}

void *init_malloc(int size, int length, enum variableType type){
    int i;
    void *arr = malloc(size*length);
    for(i=0; i<length; i++){
        switch(type){
            case INT:
                ((int*)arr)[i] = 0;
                break;
            case INT_POINTER:
                ((int**)arr)[i] = NULL;
                break;
            case DOUBLE:
                ((double*)arr)[i] = 0;
                break;
            default:
                break;
        }
    }
    return arr;
}

void print_arr(int **arr,int dimension)
{
    int index_row,index_col;
    for(index_row=0; index_row<dimension; index_row++){
        for(index_col=0; index_col<dimension; index_col++)
        {
            printf("%d ",arr[index_row][index_col]);
        }
        printf("\n");
    }
    printf("\n\n");
}
