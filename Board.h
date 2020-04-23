#ifndef BIGPROJECT_BOARD_H
#define BIGPROJECT_BOARD_H


/*the board module contains the board struct, which is at the heart of the program
 *it also contains basic functions that can be used to manipulate the board, and don't require advanced computation*/

/*status of game*/
enum gameMode {InitMode=1, SolveMode=2, EditMode=3};

/*struct containing a state of the board from the game history (for undo/redo purposes)*/
typedef struct node{
    int **arr;
    struct node* next;
    struct node* prev;
}Node;

/*holder of moves timeline (undo/redo change the head position)*/
typedef struct linked_list{
    Node *curr,*head;
}List;

/*board - contains all relevant information about the state of the game*/
typedef struct board{
    int **arr, **fixed,**error;
    int dimension, row_per_block,col_per_block,mark_errors;
    List *lst;
    enum gameMode mode;

}Board;

List *create_list();/*create the timeline of moves*/
Node* create_node(Board* b);/* create holder for row,column,value*/
Node* add(Board* b);/*add last move to the moves timeline*/
void undo(Board* b);/*Undo a previous move done by the user*/
void redo(Board* b);/*Redo a move previously undone by the user*/
void reset_list(Board* b);/*Undo all moves, reverting the board to its original loaded state*/

Board* create_board(int dimension,int row_per_block,int col_per_block);/* create board game*/
Board* duplicateBoard(Board* b);/*creates a new board with an identical arr to a given board*/
void destroy_board(Board* board);/*free memory allocated for board*/
void print_board(Board* b);/*Prints the board to the user*/

#endif /*BIGPROJECT_BOARD_H*/
