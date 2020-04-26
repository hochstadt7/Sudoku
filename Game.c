#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "FileManager.h"
#include "ValidBoard.h"
#include "MainAux.h"
#include "ILP.h"
/*the game module contains all the main functions used to manipulate the board, with the exceptions of a few exceptions
 *which are distributed in designated files, mainly due to thematic similarity*/
/*give a hint to a value in a specified square*/
void hint(int x, int y, Board *b) {
    int **arr, **fixed, **error;
    int dimension;
    int res;
    dimension = b->dimension;
    arr = b->arr;
    fixed = b->fixed;
    error = b->error;
    if(x<0 || y<0 || x>dimension || y>dimension){
        printf("Error: the provided parameters are out of bounds.\n");
        return;
    }
    x--;
    y--;
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
    res = hintLP(b, x, y);
    if(res>0)
        printf("Hint: set %d, %d to %d\n", y+1, x+1, res);
    else printf("No valid solution was found\n");
}
void guesshint(int x, int y, Board *b) {
    int **arr, **fixed, **error;
    int dimension;
    dimension = b->dimension;
    arr = b->arr;
    fixed = b->fixed;
    error = b->error;
    if(x<0 || y<0 || x>dimension || y>dimension){
        printf("Error: the provided parameters are out of bounds.\n");
        return;
    }
    x--;
    y--;
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
    guessHintLP(b, x, y);
}

/* set block to input value if value is legal */
void set(int x, int y, int z, Board *b) {
    int **arr, **fixed, **error;
    int dimension, row_per_block, col_per_block;
    dimension = b->dimension;
    row_per_block = b->row_per_block;
    col_per_block = b->col_per_block;
    arr = b->arr;
    fixed = b->fixed;
    error = b->error;
    if(x<0 || y<0 || z<0 || x>dimension || y>dimension || z>(dimension+1)){
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

    arr[x][y] = z;
    add(b);
    fix_error(arr, error, dimension, x, y, z, x - x % row_per_block, y - y % col_per_block, row_per_block, col_per_block);

    print_board(b);
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
    guessLP(b, threshold);
    add(b);
    print_board(b);
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
        add(new);
        print_board(new);
        return new;
    }
    return old;
}

Board* solve(char *link, Board *old) {
    Board *new=load(link, SolveMode);
    if(new!=NULL){
        /*if edit didnt fail, free current board memory "forget him"*/
        new->mode=SolveMode;
        destroy_board(old);
        check_fixed_cells_validity(new);
        add(new);
        print_board(new);
        return new;
    }
    return old;
}

void setMarkErrors(int mark_errors, Board *b) {
    b->mark_errors=mark_errors;
}

int validate(Board *b){
    int **error;
    int dimension;
    int res;
    dimension = b->dimension;
    error = b->error;
    if(is_erroneous(error,dimension))
    {
        printf("Validation can't be executed because board is erroneous.\n");
        return 0;
    }
    res = validateLP(b);
    if(res){
        printf("The board is solvable\n");
        return 1;
    }
    else {
        printf("No valid solution was found\n");
        return 0;
    }
}


/*undo move*/
void undo(Board* b){
    int **arr;
    List *lst;
    arr = b->arr;
    lst = b->lst;

    if(lst->curr==NULL || lst->curr->prev==NULL){
        /*no move to undo*/
        printf("Nothing to undo.\n");
        return;
    }
    lst->curr = lst->curr->prev;
    copy_arrays(lst->curr->arr, arr, b->dimension);
    reCalcErrors(b);
    print_board(b);
}
/*redo move*/
void redo(Board* b) {
    int **arr;
    List *lst;
    arr = b->arr;
    lst = b->lst;
    if(lst->curr==NULL || lst->curr->next==NULL){
        /*no move to undo*/
        printf("Nothing to redo.\n");
        return;
    }
    lst->curr = lst->curr->next;
    copy_arrays(lst->curr->arr, arr, b->dimension);
    reCalcErrors(b);
    print_board(b);
}
void reset_list(Board* b){
    /*undo all moves*/
    int **arr;
    List *lst;
    arr = b->arr;
    lst = b->lst;
    if(lst->head==NULL)
        return;
    while (lst->curr->prev!=NULL)
    {
        lst->curr=lst->curr->prev;
    }
    copy_arrays(lst->curr->arr, arr, b->dimension);
    reCalcErrors(b);
    print_board(b);
}

/*save the board in a new file in the specified link*/
void save(char *link, Board *board) {
    int index_row, index_col;
    char suffix;
    FILE *dest = NULL;
    /*check if board is erroneous, and in edit mode or not solvable (need to add not solvable condition after implemnting ilp)*/
    if (board->mode == EditMode && (is_erroneous(board->error, board->dimension) || !validate(board))) {
        printf("erroneous boards may not be saved in 'edit' mode.\n");
        return;
    }
    printf("Saving...\n");
    dest = fopen(link, "w");
    if (dest == NULL) {
        printf("Invalid filepath.\n");
        exit(0);
    }
    fprintf(dest, "%d %d\n", board->row_per_block, board->col_per_block);
    for (index_row = 0; index_row < board->dimension; index_row++) {
        for (index_col = 0; index_col < board->dimension; index_col++) {
            if(index_col == board->dimension-1){
                suffix = '\n';
            }
            else{
                suffix = ' ';
            }
            if ((board->fixed[index_row][index_col] == 1 || board->mode == EditMode) && board->arr[index_row][index_col]>0) {
                fprintf(dest, "%d.%c", board->arr[index_row][index_col], suffix);
            } else {
                fprintf(dest, "%d%c", board->arr[index_row][index_col], suffix);
            }
        }
    }
    fclose(dest);
    printf("Saved board to %s\n", link);
}
