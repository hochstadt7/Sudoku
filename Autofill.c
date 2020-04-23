#include <stdio.h>
#include "Board.h"
#include "ValidBoard.h"
#include "MainAux.h"
/*the autofill module contains a single function, whose purpose is to fill board cells that only have one possible valid value*/
void autofill(Board *b) {
    int **arr, **error;
    int dimension, row_per_block, col_per_block;
    int row, col, num, count, candidate = 0;
    Board *temp;
    dimension = b->dimension;
    row_per_block = b->row_per_block;
    col_per_block = b->col_per_block;
    arr = b->arr;
    error = b->error;
    if (is_erroneous(error, dimension)) {
        printf("Can't autofill erroneous board.\n");
        return;
    }
    temp=duplicateBoard(b);
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (arr[row][col] == 0) {
                count = 0;
                for (num = 1; num < dimension + 1; num++) {
                    if (is_valid(arr,dimension,row,col,arr[row][col],row_per_block,col_per_block)) {
                        count++;
                        candidate = num;
                    }
                }
                if (count == 1) {
                    temp->arr[row][col] = candidate;
                }
            }
        }
    }
    copy_arrays(temp->arr, arr, dimension);
    add(b);
    destroy_board(temp);
    print_board(b);
}
