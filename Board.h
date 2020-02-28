//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_BOARD_H
#define BIGPROJECT_BOARD_H
//#include "History.h"

/*status of game*/
enum status {Init=1, Solve=2, Edit=3};

typedef struct node{
    int row,col,val;
    struct node* next;
    struct node* prev;
}Node;

/*holder of moves's timeline*/
typedef struct linked_list{
    int row,col;
    Node *curr,*head;

}List;

List *create_list();/*create the timeline of moves*/
Node* create_node();/* create holder for row,column,value*/
void add(List* lst,int row,int col,int val);/*add last move to the moves timeline*/
void undo(int **arr,List *lst);/*cancel last move*/
void redo(int **arr,List *lst);/*redo last move*/
void print_list(List *lst);/*print the list*/
void reset_list(int **arr,int**fixed,int **error,int dimension,int row_per_block,int col_per_block,List *lst);/*cancel all moves*/

/*board game*/
typedef struct board{
    int **arr, **fixed,**solution,**error;
    int dimension, row_per_block,col_per_block,mark_error,is_over;
    List *lst;
    enum status mode;

}Board;
Board* create_board(int dimension,int row_per_block,int col_per_block);/* create board game*/
void destroy_board(Board* board);/*free memory allocated for board*/
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block);/*printing board*/


#endif //BIGPROJECT_BOARD_H
