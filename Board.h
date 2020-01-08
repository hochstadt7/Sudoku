//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_BOARD_H
#define BIGPROJECT_BOARD_H
enum status {Init=1, Solve=2, Edit=3};
typedef struct board{
    int **arr, **fixed,**solution,**error;
    int dimension, row_per_block,col_per_block;
    enum status mode;

}Board;
Board* create_board(int dimension,int row_per_block,int col_per_block);
void print_board(Board* board);
#endif //BIGPROJECT_BOARD_H
