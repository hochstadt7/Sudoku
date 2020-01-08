//
// Created by LENOVO on 02/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "History.h"


Node* create_node(int row, int col){
Node *temp= (Node *) malloc(sizeof(Node));
temp->row=row;
temp->col=col;
temp->next=NULL;
temp->prev=NULL;
return temp;
}

typedef struct linked_list{
    int row,col;
    Node *curr,*head;

}List;


void add(List* lst,int row,int col){
Node* node=create_node(row,col);
if(lst->head==NULL){
    lst->head=node;
    lst->curr=node;
}
else{
    lst->curr->next=node;
    node->prev=lst->curr;
    lst->curr=lst->curr->next;
}
}

void undo(List* lst){
    if(lst->head==NULL||lst->curr->prev==NULL){
        printf("Error");
        return;
    } else{
        lst->curr=lst->curr->prev;
    }
}

void redo(List* lst){
    if(lst->head==NULL||lst->curr->next==NULL){
        printf("Error");
        return;
    } else{
        lst->curr=lst->curr->next;
    }
}

void reset_list(List *lst){
    if(lst->head==NULL)
        return;
    while (lst->curr->prev!=NULL)
    {
        lst->curr=lst->curr->prev;
    }
}

void free_lst(List *lst){
    if(lst->curr==NULL)
    {
        free(lst);
        return;
    }
    while (lst->curr->next!=NULL)
        lst->curr=lst->curr->next;
    while (lst->curr->prev!=NULL) {
        lst->curr = lst->curr->prev;
        free(lst->curr->next);
    }
    free(lst->curr);
    free(lst);
}
