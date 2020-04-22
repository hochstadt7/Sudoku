#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "FileManager.h"
#include "ValidBoard.h"
#include "MainAux.h"
#include "ILP.h"
/*give a hint to a value in a specified square*/
void hint(int x, int y, Board *b) {
    int **arr, **fixed, **error;
    int dimension;
    Response* res;
    dimension = b->dimension;
    arr = b->arr;
    fixed = b->fixed;
    error = b->error;
    if(is_erroneous(error,dimension)) {/*board is erroneous*/
        printf("You can't get a hint from an erroneous board\n");
        return;
    }
    if(fixed[x][y]==1){/*specified cell is fixed*/
        printf("Can't give a hint to a fixed cell.\n");
        return;
    }
    if(arr[x][y]!=0){/*specified cell is full*/
        printf("Can't give a hint to a full cell.\n");
        return;
    }
    res = calc(b);
    if(res->valid)
        printf("Hint: set %d, %d to %d\n", x, y, res->solution->arr[x][y]);
    else printf("No valid solution was found\n");
    destroy_board(res->solution);
    free(res);
}
/*save the board in a new file in the specified link*/
void save(char *link, Board *board) {
    int index_row, index_col;
    FILE *dest = NULL;
    /*check if board is erroneous, and in edit mode or not solvable (need to add not solvable condition after implemnting ilp)*/
    if (board->mode == EditMode && is_erroneous(board->error, board->dimension)) {
        printf("In edit mode erroneous boards may not be saved.\n");
        return;
    }
    dest = fopen(link, "w");
    if (dest == NULL) {
        printf("Error in save.\n");
        exit(0);
    }
    if (board->mode == EditMode) {/* in such a case all filled cells are fixed*/
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
            fprintf(dest, "\n");/*validate it is nessecery last iteration*/
        }
        fclose(dest);
}

/* set block to input value if value is legal*/
void set(int x, int y, int z, Board *b) {
    int **arr, **fixed, **error;
    int dimension, row_per_block, col_per_block;
    dimension = b->dimension;
    row_per_block = b->row_per_block;
    col_per_block = b->col_per_block;
    arr = b->arr;
    fixed = b->fixed;
    error = b->error;
    if(x<0 || y<0 || z<1 || x>dimension || y>dimension || z>(dimension+1)){
        printf("Error: the provided parameters are out of bounds.\n");
        return;
    }
    x--;
    y--;
    /*if setting to same value before*/
    if(arr[x][y]==z){
        add(b);
        print_board(b);
        return;
    }

    if (fixed[x][y] == 1 && b->mode == SolveMode) {
        printf("Error: cell is fixed.\n");
        return;
    }

    if (z == 0) {
        fix_error(arr, error, dimension, x, y, 0, x - x % row_per_block, y - y % col_per_block, row_per_block,
                  col_per_block);
        add(b);
        arr[x][y] = 0;
        print_board(b);
        return;
    }

    /*TODO: change condition here, error value is ok*/
    if (is_valid(arr, dimension, x, y, z, row_per_block, col_per_block)) {
        arr[x][y] = z;
        add(b);
        fix_error(arr, error, dimension, x, y, z, x - x % row_per_block, y - y % col_per_block, row_per_block, col_per_block);
    }
}

void guess(float threshold, Board *b){
    int **error;
    int dimension;
    dimension = b->dimension;
    error = b->error;
    if(is_erroneous(error,dimension))
    {
        printf("Guess can't be executed because board is erroneous.\n");
        return;;
    }
    printf("%f",threshold);
}

void exit_game(Board *board){
    destroy_board(board);
    printf("Exiting game...\n");
    exit(0);
}

/*check whether fixed cells are legal in solve mode*/
void check_fixed_cells_validity(Board *b){
    int **arr, **error;
    int dimension, row_per_block, col_per_block;
    int index_row,index_col;
    dimension = b->dimension;
    row_per_block = b->row_per_block;
    col_per_block = b->col_per_block;
    arr = b->arr;
    error = b->error;
    /*find_solution(); find solution using ILP*/
    for(index_row=0; index_row<dimension; index_row++ ){
        for(index_col=0; index_col<dimension; index_col++){
            if(arr[index_row][index_col]!=0) {
                fix_error(arr, error, dimension, index_row, index_col, arr[index_row][index_col],
                          index_row - index_row % row_per_block, index_col - index_col % col_per_block, row_per_block,col_per_block);
            }
        }
    }
}

Board* edit(char *link, Board *old) {
    Board *new;
    if(link != NULL && strcmp(link, "")!=0){
        new = load(link, EditMode);
    }
    else{
        new = create_board(9, 3, 3);
    }
    if(new!=NULL){
        /*if edit didnt fail, free current board memory "forget him"*/
        new->mode=EditMode;
        destroy_board(old);
        /*not sure that this call should exist in edit mode*/
        /*check_fixed_cells_validity(new->arr,new->fixed,new->solution,new->error,new->dimension,new->row_per_block,new->col_per_block);*/
    }
    return new;
}

Board* solve(char *link, Board *old) {
    Board *new=load(link, SolveMode);
    if(new!=NULL){
        /*if edit didnt fail, free current board memory "forget him"*/
        new->mode=SolveMode;
        destroy_board(old);
        check_fixed_cells_validity(new);
    }
    return new;
}

void setMarkErrors(int mark_errors, Board *b) {
    b->mark_errors=mark_errors;
}

void validate(Board *b){
    int **error;
    int dimension;
    Response* res;
    dimension = b->dimension;
    error = b->error;
    if(is_erroneous(error,dimension))
    {
        printf("Validation can't be executed because board is erroneous.\n");
        return;;
    }
    res = calc(b);
    if(res->valid)
        printf("The board is solvable\n");
    else printf("No valid solution was found\n");
    destroy_board(res->solution);
    free(res);
}
