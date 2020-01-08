#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Board.h"
#include "MainAux.h"
#include "Game.h"
#include "FileManager.h"
#define DIMENSION 9
#define ROWPERBLOCK 3
#define COLPERBLOCK 3

void print_me(Board *game)
{
    int index_row,index_col;
    for(index_row=0; index_row<game->dimension; index_row++){
        for(index_col=0; index_col<game->dimension; index_col++)
        {
            printf("%d ",game->fixed[index_row][index_col]);
        }
        printf("\n");
    }
}

int main() {

    Board *game=load("C:\\Users\\LENOVO\\Documents\\New folder\\type");
    print_board(game);
    print_me(game);

    return 0;
}
