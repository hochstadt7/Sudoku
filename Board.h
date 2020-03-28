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
Node* add(List* lst,int row,int col,int val);/*add last move to the moves timeline*/
void undo(int **arr,List *lst);/*Undo a previous move done by the user*/
void redo(int **arr,List *lst);/*Redo a move previously undone by the user*/
void print_list(List *lst);/*print the list*/
void reset_list(int **arr,int**fixed,int **error,int dimension,int row_per_block,int col_per_block,List *lst);/*Undo all moves, reverting the board to its original loaded state*/

/*board game*/
typedef struct board{
    int **arr, **fixed,**solution,**error;
    int dimension, row_per_block,col_per_block,mark_error,is_over;
    List *lst;
    enum status mode;

}Board;
Board* create_board(int dimension,int row_per_block,int col_per_block);/* create board game*/
void destroy_board(Board* board);/*free memory allocated for board*/
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block);/*Prints the board to the user*/


#endif //BIGPROJECT_BOARD_H
