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


