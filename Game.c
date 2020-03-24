#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "ValidBoard.h"
#include "FileManager.h"
#include "MainAux.h"
/*give a hint to a value in a specified square*/
void hint(int **arr,int **fixed,int **solution,int **error,int dimension, int y, int x) {
    if(is_errorneous(error,dimension)) {//board is errorneous
        printf("You can't get a hint from an errorneous board\n");
        return;
    }
    if(fixed[x][y]==1){//specified cell is fixed
        printf("Can't give a hint to a fixed cell\n");
        return;
    }
    if(arr[x][y]!=0){//specified cell is full
        printf("Can't give a hint to a full cell");
        return;
    }
    //need to find if solvable using ilp and than:
    printf("Hint: set cell to %d\n", solution[x][y]);

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
        printf("Error in save");
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
            print_board(arr,fixed,error,dimension,row_per_block,col_per_block);
            return;
        }
        if (fixed[x][y] == 1) {// can change in edit mode?
            printf("Error: cell is fixed\n");
            return;
        }

        if (z == 0) {
            fix_error(arr, error, dimension, x, y, 0, x - x % row_per_block, y - y % col_per_block, row_per_block,
                      col_per_block);
            if(!add(lst, x, y, arr[x][y]))// failed allocation
                return;
            arr[x][y] = 0;
            print_board(arr, fixed, error, dimension, row_per_block, col_per_block);
            return;
        }
//change condition here,error value is ok
      //  if (is_valid(arr, dimension, x, y, z, row_per_block, col_per_block)) {
    if(!add(lst, x, y, arr[x][y]))
        return;
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

    void mark_errors(int mark, Board *board) {
        board->mark_error = mark;
    }

    Board* edit(char *link,Board *old, enum status mode) {
        Board *new=load(link,mode);
        if(new!=NULL){//if edit didnt fail, free current board memory "forget him"
            new->mode=Edit;
            if(old!=NULL)
        destroy_board(old);
            initialize(new->arr,new->fixed,new->solution,new->error,new->dimension,new->row_per_block,new->col_per_block);
        }
        return new;
    }


    void autofill(int **arr, int **fixed, int **error, int dimension, int row_per_block, int col_per_block, List *lst) {
        int row, col, num, count, candidate = 0;
        int **temp;
        if (is_errorneous(error, dimension)) {
            printf("Can't autofill errorneous board.\n");
            return;
        }
        temp=first_init(dimension);
        for (row = 0; row < dimension; row++) {
            for (col = 0; col < dimension; col++) {
                if (arr[row][col] == 0) {
                    count = 0;
                    for (num = 1; num < dimension + 1; num++) {
                        if (is_valid(arr, dimension, row, col, num, row_per_block, col_per_block)) {
                            count++;
                            candidate = num;
                        }
                    }
                    if (count == 1) {
                        temp[row][col] = candidate;
                    }
                }
            }
        }
        for (row = 0; row < dimension; row++) {
            for (col = 0; col < dimension; col++) {
                if (temp[row][col] != 0) {
                    candidate = temp[row][col];
                    if(!add(lst, row, col, arr[row][col]))//allocation failed
                        return;;
                    arr[row][col] = candidate;//add to memory?
                    fix_error(arr, error, dimension, row, col, candidate, row - row % row_per_block,
                              col - col % col_per_block, row_per_block, col_per_block);
                }
            }
        }
        free_arrays(temp,dimension);
        print_board(arr, fixed, error, dimension, row_per_block, col_per_block);
    }

    void guess(int x,int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){
        if(is_errorneous(error,dimension))
        {
            printf("Validation can't be executed because board is errorneous.\n");
            return;;
        }
    }

    /*void generate(int x,int y,int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){

    }*/
