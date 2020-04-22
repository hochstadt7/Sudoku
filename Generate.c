#include <stdio.h>
#include <stdlib.h>
#include "MainAux.h"
#include "Board.h"
#include "ValidBoard.h"
#include "ILP.h"

/*check whether there are x empty cells*/
int there_are_x_empty(int **arr, int dimension, int x) {
    int count_empty = 0, row, col;
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (arr[row][col] == 0)
                count_empty++;
        }
    }
    if (count_empty < x)
        return -1;
    return count_empty;
}

/*randomly choose legal value for cell in specified row and column*/
int choose_legal(Board *b, int row, int col) {
    int count, val;
    int dimension = b->dimension;
    int *legal = malloc(dimension * sizeof(int));
    count = 0;
    if (!legal) {
        printf("Allocation failed.\n%d%d", row, col);
        exit(0);
    }
    for (val = 1; val < dimension + 1; val++) {
        if (is_valid(b->arr, dimension, row, col, val, b->row_per_block, b->col_per_block)) {
            legal[count] = val;
            count++;
        }
    }
    if (count == 0) {
        free(legal);
        return 0;
    }
    count = rand() % count;
    count = legal[count];
    free(legal);
    return count;
}

/*randomly choose X cells and fill each selected cell with a random legal value */
int fill_x_cells(Board *b, int x) {
    int dimension, row, col, random, val, emptyCellCount = 0, alreadySetCount = 0;
    int **arr;
    int *selectedCells;
    arr = b->arr;
    dimension = b->dimension;
    selectedCells = malloc(sizeof(int)*dimension*dimension);
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (arr[row][col] == 0) {
                selectedCells[emptyCellCount] = row*dimension+col;
                emptyCellCount++;
            }
        }
    }
    while(alreadySetCount<x){
        random = rand() % emptyCellCount;
        row = selectedCells[random] / dimension;
        col = selectedCells[random] % dimension;
        if(arr[row][col]){
            continue;
        }
        val = choose_legal(b, row, col);
        if(val){
            alreadySetCount++;
            arr[row][col] = val;
        }
    }
    free(selectedCells);
    return 1;
}

/*randomly choose Y cells out of the entire board and clear the values of all other cells*/
int keep_y_cells(Board *b, int y) {
    int dimension, row, col, random, alreadyUnsetCount = 0;
    int **arr;
    arr = b->arr;
    dimension = b->dimension;
    while(alreadyUnsetCount<(dimension * dimension) - y){
        random = rand() % (dimension * dimension);
        row = random / dimension;
        col = random % dimension;
        if(arr[row][col]){
            arr[row][col] = 0;
            alreadyUnsetCount++;
        }
    }
    return 1;
}

/*Generates a puzzle by randomly filling X empty cells with legal values, running ILP to solve the board, and then clearing all but Y random cells*/
void generate(int x, int y, Board *b) {
    int iteration = 0, count_empty, dimension;
    int **arr, **error;
    Board *temp;
    Response *res;

    arr = b->arr;
    error = b->error;
    dimension = b->dimension;

    if (is_erroneous(error, dimension)) {
        printf("erroneous board can't be generated.\n");
        return;
    }
    count_empty = there_are_x_empty(arr, dimension, x);
    if (count_empty == -1) {
        printf("There aren't x empty cells.\n");
        return;
    }
    temp = duplicateBoard(b);
    while (iteration < 1000) {
        copy_arrays(arr, temp->arr, dimension);/*the original array should remain unaltered until the process succeeds*/
        if (!fill_x_cells(temp, x)) {/*failure in allocation/no legal value for some cells*/
            return;
        }
        res = calc(temp);
        if (!res || !res->valid) {
            iteration++;
            continue;
        }
        destroy_board(temp);
        temp = duplicateBoard(res->solution);
        if (!keep_y_cells(temp, y))/*failure in allocation*/
            return;
        add(temp);
        destroy_board(temp);
        destroy_board(res->solution);
        free(res);
        return;
    }
    printf("Generation failed.\n");
}
