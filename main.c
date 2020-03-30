#include <stdio.h>
#include <stdlib.h>
//#include "Game.h"
//#include "Board.h"
#include "MainAux.h"
#include "Game.h"
#include "FileManager.h"
#include "ValidBoard.h"
#define DIMENSION 9
#define ROWPERBLOCK 3
#define COLPERBLOCK 3
#include "Solve.h"
#include "Stack.h"
#include "TestGame.h"
//#include "History.h"

void print_me(int **arr,int dimension)
{
    int index_row,index_col;
    for(index_row=0; index_row<dimension; index_row++){
        for(index_col=0; index_col<dimension; index_col++)
        {
            printf("%d ",arr[index_row][index_col]);
        }
        printf("\n");
    }
}

void test_all() {

    Board *game=edit("C:\\Users\\LENOVO\\Documents\\New folder\\type",NULL,Solve);
    set(game->arr,game->error,game->dimension,game->fixed,3,4,1,game->row_per_block,game->col_per_block,game->lst);
    undo(game->arr,game->lst);
    autofill(game->arr,game->fixed,game->error,game->dimension,game->row_per_block,game->col_per_block,game->lst);
    redo(game->arr,game->lst);
    undo(game->arr,game->lst);
    redo(game->arr,game->lst);
    print_me(game->arr,game->dimension);

    destroy_board(game);

}
int main() {
test_all();
printf("Winner.\n");
    return 0;
}