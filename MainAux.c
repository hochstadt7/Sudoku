#include <stdio.h>
#include <stdlib.h>
#include "ValidBoard.h"
/*initilaize the array*/
int** first_init(int dimension) {
    int i;
    int **arr=(int **) calloc(dimension , sizeof(int *));
    if(!arr)
    {
        printf("first_init failed");
        return NULL;
    }
    for (i = 0; i < dimension; i++) {
        arr[i] = (int *) calloc(dimension , sizeof(int));
        if (!arr[i] ) {
            printf("first_init failed");
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
}
/*make a copy of a given array*/
void copy_arrays(int **copy, int**paste,int dimension)
{
    int index_row,index_col;
    for(index_row=0; index_row<dimension; index_row++){
        for(index_col=0; index_col<dimension; index_col++)
        {
            paste[index_row][index_col]=copy[index_row][index_col];
        }
    }

}
/*find wether the board is errorneous*/
int is_errorneous(int **error,int dimension){
    int row,col;
    for(row=0; row<dimension; row++){
        for(col=0; col<dimension; col++){
            if(error[row][col]==1)
                return 1;
        }
    }
    return 0;
}

void initialize(int **arr,int **fixed,int **solution,int **error,int dimension, int row_per_block,int col_per_block){
    int index_row,index_col;
//find_solution(); find solution using ILP
for(index_row=0; index_row<dimension; index_row++ ){
    for(index_col=0; index_col<dimension; index_col++){
        if(arr[index_row][index_col]!=0) {
            fix_error(arr, error, dimension, index_row, index_col, arr[index_row][index_col],
                      index_row - index_row % row_per_block, index_col - index_col % col_per_block, row_per_block,col_per_block);

        }
    }

}
}
