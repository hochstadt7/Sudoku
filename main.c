#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Board.h"
#define DIMENSION 9
#define ROWPERBLOCK 3
#define COLPERBLOCK 3

int main() {
    int **arr,**fixed,**solution;
    Board *game=create_board(arr,fixed,solution,DIMENSION,ROWPERBLOCK,COLPERBLOCK);
    return 0;
}
