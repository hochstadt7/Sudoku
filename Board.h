//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_BOARD_H
#define BIGPROJECT_BOARD_H
//#include "History.h"

/*status of game*/
enum status {Init=1, Solve=2, Edit=3};

/*board game*/
typedef struct board{
    int **arr, **fixed,**solution,**error;
    int dimension, row_per_block,col_per_block,mark_error,is_over;
   // List *lst;// need to solve this
    enum status mode;

}Board;
Board* create_board(int dimension,int row_per_block,int col_per_block);/* create board game*/
void destroy_board(Board* board);/*free memory allocated for board*/
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block);/*printing board*/
#endif //BIGPROJECT_BOARD_H
