//
// Created by LENOVO on 02/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "History.h"


List *create_list(){
List *tmp=(List *)malloc(sizeof(List));
tmp->head=NULL;tmp->curr=NULL;
return tmp;
}

Node* create_node(int row, int col,int val){
Node *temp= (Node *) malloc(sizeof(Node));
if(temp==NULL) {
    printf("Node allocation failed");
    return NULL;
}
temp->row=row;temp->col=col;temp->val=val;
temp->next=NULL;temp->prev=NULL;
return temp;
}


void add(List* lst,int row,int col,int val){
Node* node=create_node(row,col,val);
if(node==NULL) {
    printf("Node allocation has failed\n");
    return;
}
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

void undo(List* lst,Board *board){
    if(lst->head==NULL||lst->curr->prev==NULL){
        printf("Cant undo");
        return;
    } else{
        lst->curr=lst->curr->prev;
        board->arr[lst->curr->row][lst->curr->col]=lst->curr->val;
    }
}

void redo(List* lst,Board *board){
    if(lst->head==NULL||lst->curr->next==NULL){
        printf("Cant redo");
        return;
    } else{
        lst->curr=lst->curr->next;
        board->arr[lst->curr->row][lst->curr->col]=lst->curr->val;
    }
}

void reset_list(List *lst,Board *board){
    if(lst->head==NULL)
        return;
    while (lst->curr->next!=NULL)
        lst->curr=lst->curr->next;
    while (lst->curr->prev!=NULL)
    {
        lst->curr=lst->curr->prev;
        board->arr[lst->curr->row][lst->curr->col]=lst->curr->val;
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
void print_list(List *lst){
    Node* tmp=lst->head;
    while (tmp!=NULL){
        printf("row=%d col=%d\n",tmp->row,tmp->col);
        tmp=tmp->next;
    }
}