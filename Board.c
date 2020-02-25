#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "MainAux.h"
#include "History.h"

Board* create_board(int dimension,int row_per_block,int col_per_block){
Board* board=(Board*) malloc(sizeof(Board));
if(!board) {
    printf("create_board failed");
    return NULL;
}
board->arr=first_init(dimension);
if(board->arr==NULL) {
    printf("Create_board failed");
    free(board);
    return NULL;
}
board->fixed=first_init(dimension);
if(board->fixed==NULL)
{
    printf("Create_board failed");
    free(board->arr);
    free(board);
    return  NULL;
}
board->solution=first_init(dimension);
    if(board->solution==NULL)
    {
        printf("Create_board failed");
        free(board->fixed);
        free(board->arr);
        free(board);
        return NULL;
    }
    board->error=first_init(dimension);
    if(board->error==NULL)
    {
        printf("Create_board failed");
        free(board->error);
        free(board->fixed);
        free(board->arr);
        free(board);
        return NULL;
    }
   // board->lst=create_list();
   board->dimension=dimension;board->mark_error=0;board->is_over=0;
board->row_per_block=row_per_block;
board->col_per_block=col_per_block;
board->mode=Init;
return board;
}

void destroy_board(Board* board){
    if(!board)
        return;
    free(board->error);
    free(board->solution);
    free(board->fixed);
    free(board->arr);
    free(board);
}
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){
    int index_row, index_col, index_block, blocks_per_row,num_dash;
    blocks_per_row = dimension / col_per_block;
    num_dash=blocks_per_row*4*col_per_block+1;
    for (index_row = 0; index_row < dimension; index_row++) {
        if (index_row % row_per_block == 0) {
            for(index_block=0; index_block<num_dash; index_block++) {
                printf("-");
            }
            printf("\n");
        }
        for (index_block = 0; index_block < blocks_per_row; index_block++) {
            printf("| ");
            for (index_col = 0; index_col < col_per_block; index_col++) {
                if (arr[index_row][index_col + col_per_block * index_block] != 0) {

                    if (fixed[index_row][index_col + col_per_block * index_block] != 0)
                        printf(" %2d.", arr[index_row][index_col + col_per_block * index_block]);
                    else if(error[index_row][index_col + col_per_block * index_block] != 0){
                    printf(" %2d*", arr[index_row][index_col + col_per_block * index_block]);
                    }
                    else
                        printf("%2d ", arr[index_row][index_col + col_per_block * index_block]);
                } else {
                    printf("   ");
                }
            }
        }
        printf("|\n");
    }
    printf("----------------------------------\n");
}

