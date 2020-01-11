//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_HISTORY_H
#define BIGPROJECT_HISTORY_H
#include "Board.h"

typedef struct node{
    int row,col,val;
    struct node* next;
    struct node* prev;
}Node;

typedef struct linked_list{
    int row,col;
    Node *curr,*head;

}List;

List *create_list();
void add(List* lst,int row,int col,int val);
void undo(List* lst,Board *board);
void redo(List* lst,Board *board);
void print_list(List *lst);

#endif //BIGPROJECT_HISTORY_H
