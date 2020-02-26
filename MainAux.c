#include <stdio.h>
#include <stdlib.h>
#include "Board.h"


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




