/**/
/**/ Created by LENOVO on 02/01/2020.
/**/

#ifndef BIGPROJECT_HISTORY_H
#define BIGPROJECT_HISTORY_H
/*#include*/ "Board.h"

/*holder of assignment for squares*/
/*typedef struct node{
    int row,col,val;
    struct node* next;
    struct node* prev;
}Node;

/*holder of moves's timeline*/
/*typedef struct linked_list{
    int row,col;
    Node *curr,*head;

}List;

List *create_list();/*create the timeline of moves*/
/*Node*/* create_node();/* create holder for row,column,value*/
/*void*/ add(List* lst,int row,int col,int val);/*add last move to the moves timeline*/
/*void*/ undo(int **arr,List *lst);/*cancel last move*/
/*void*/ redo(int **arr,List *lst);/*redo last move*/
/*void*/ print_list(List *lst);/*print the list*/
/*void*/ reset_list(List *lst,Board *board);/*cancel all moves*/

#endif /*BIGPROJECT_HISTORY_H*/
