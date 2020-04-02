#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "ValidBoard.h"
#include "MainAux.h"
/*give a hint to a value in a specified square*/
void hint(int **arr,int **fixed,int **solution,int **error,int dimension, int y, int x) {
    if(is_errorneous(error,dimension)) {//board is errorneous
        printf("You can't get a hint from an errorneous board\n");
        return;
    }
    if(fixed[x][y]==1){//specified cell is fixed
        printf("Can't give a hint to a fixed cell.\n");
        return;
    }
    if(arr[x][y]!=0){//specified cell is full
        printf("Can't give a hint to a full cell.\n");
        return;
    }
    //need to find if solvable using ilp and than:
    printf("Hint: set cell to %d.\n", solution[x][y]);

}
/*save the board in a new file in the specified link*/
void save(char *link,Board *board) {
    int index_row, index_col;
    //check if board is erroneous, and in edit mode or not solvable (need to add not solvable condition after implemnting ilp)
    if (board->mode == Edit && is_errorneous(board->error, board->dimension)) {
        printf("In edit mode errorneous boards may not be saved.\n");
        return;
    }
    FILE *dest = NULL;
    dest = fopen(link, "w");
    if (dest == NULL) {
        printf("Error in save.\n");
        exit(0);
    }
    if (board->mode == Edit) {// in such a case all filled cells are fixed
        for (index_row = 0; index_row < board->dimension; index_row++) {
            for (index_col = 0; index_col < board->dimension; index_col++) {
                if (board->arr[index_row][index_col] != 0) {
                    board->fixed[index_row][index_col] = 1;
                }
            }
        }
    }
        fprintf(dest, "%d %d\n", board->row_per_block, board->col_per_block);

        for (index_row = 0; index_row < board->dimension; index_row++) {

            for (index_col = 0; index_col < board->dimension-1; index_col++) {
                if (board->fixed[index_row][index_col] != 1) {
                    fprintf(dest, "%d ", board->arr[index_row][index_col]);
                } else {
                    fprintf(dest, "%d. ", board->arr[index_row][index_col]);
                }

            }
            if (board->fixed[index_row][board->dimension-1] != 1) {
                fprintf(dest, "%d", board->arr[index_row][board->dimension-1]);
            } else {
                fprintf(dest, "%d.", board->arr[index_row][board->dimension-1]);
            }
            fprintf(dest, "\n");//validate it is nessecery last iteration

        }
        fclose(dest);

}

/* set block to input value if value is legal*/

    void set(int **arr, int **error, int dimension, int **fixed, int y, int x, int z, int row_per_block, int col_per_block,
        List *lst) {
        if(arr[x][y]==z){//if setting to same value before
            add(lst,x,y,arr[x][y],Normal);
            /*if(!add(lst,x,y,arr[x][y])){//even if its the same value' need to insert it to the moves list
                exit(0);
            }*/
            print_board(arr,fixed,error,dimension,row_per_block,col_per_block);
            return;
        }
        if (fixed[x][y] == 1) {// add condition-solve mode
            printf("Error: cell is fixed.\n");
            return;
        }

        if (z == 0) {
            fix_error(arr, error, dimension, x, y, 0, x - x % row_per_block, y - y % col_per_block, row_per_block,
                      col_per_block);
            add(lst,x,y,arr[x][y],Normal);
            /*if(!add(lst, x, y, arr[x][y]))// failed allocation
                exit(0);*/
            arr[x][y] = 0;
            print_board(arr, fixed, error, dimension, row_per_block, col_per_block);
            return;
        }
//change condition here,error value is ok
      //  if (is_valid(arr, dimension, x, y, z, row_per_block, col_per_block)) {
    add(lst,x,y,arr[x][y],Normal);
   /* if(!add(lst, x, y, arr[x][y]))
        exit(0);*/
    arr[x][y] = z;
            fix_error(arr, error, dimension, x, y, z, x - x % row_per_block, y - y % col_per_block, row_per_block,
                      col_per_block);
            print_board(arr, fixed, error, dimension, row_per_block, col_per_block);
        //}
        /*else {
            printf("Error: value is invalid\n");
            return;
        }*/
    }
/*Sets the "mark errors" setting to X, where X is either 0 or 1*/
    void mark_errors(int mark, Board *board) {
        board->mark_error = mark;
    }



    void guess(int x,int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){
        if(is_errorneous(error,dimension))
        {
            printf("Validation can't be executed because board is errorneous.\n");
            return;;
        }
    }



    void exit_game(Board *board){
        destroy_board(board);
        printf("Exiting game...\n");
        exit(0);
    }
