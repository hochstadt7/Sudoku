#include <stdio.h>
#include <stdlib.h>


int** first_init(int dimension) {
    int i;
    int **arr=(int **) malloc(dimension * sizeof(int *));
    if(!arr)
    {
        return NULL;
    }
    for (i = 0; i < dimension; i++) {
        arr[i] = (int *) malloc(dimension * sizeof(int));
        if (!arr[i] ) {
            return NULL;
        }
    }
    return arr;

}

