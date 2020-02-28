#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "MainAux.h"
//#include "History.h"


List *create_list() {
    List *tmp = (List *) malloc(sizeof(List));
    if(tmp==NULL){
        printf("List allocation failed");
        return NULL;
    }
    tmp->head = NULL;
    tmp->curr = NULL;
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
    Node *tmp;
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
        tmp=lst->curr->next; //all the redo part of the list need to be cleared (memory leak)
        if(tmp!=NULL) {
            while (tmp->next!=NULL) {
                tmp=tmp->next;
                free(tmp->prev);
            }
            free(tmp);
        }

        lst->curr->next=node;
        node->prev=lst->curr;
        lst->curr=lst->curr->next;
    }
}
void reset_list(int **arr,int**fixed,int **error,int dimension,int row_per_block,int col_per_block,List *lst){
    if(lst->head==NULL)
        return;
    while (lst->curr->next!=NULL)
        lst->curr=lst->curr->next;
    while (lst->curr->prev!=NULL)
    {
        lst->curr=lst->curr->prev;
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
    }
    print_board(arr,fixed,error,dimension,row_per_block,col_per_block);
}

void free_lst(List *lst){
    if(lst->head==NULL)
    {
        free(lst);
        return;
    }
    while (lst->curr->next!=NULL) {
        lst->head = lst->head->next;
        free(lst->head->prev);
    }
    free(lst->head);
    free(lst);
}
void print_list(List *lst) {
    Node *tmp = lst->head;
    while (tmp != NULL) {
        printf("row=%d col=%d value=%d\n", tmp->row, tmp->col,tmp->val);
        tmp = tmp->next;
    }
}

Board* create_board(int dimension,int row_per_block,int col_per_block){
Board* board=(Board*) malloc(sizeof(Board));
if(!board) {
    printf("Create_board failed");
    return NULL;
}
board->arr=first_init(dimension);
if(board->arr==NULL) {
    printf("Create_board failed");
    free(board);
    return NULL;
}
board->fixed=first_init(dimension);
if(board->fixed==NULL)
{
    printf("Create_board failed");
    free(board->arr);
    free(board);
    return  NULL;
}
board->solution=first_init(dimension);
    if(board->solution==NULL)
    {
        printf("Create_board failed");
        free(board->fixed);
        free(board->arr);
        free(board);
        return NULL;
    }
    board->error=first_init(dimension);
    if(board->error==NULL)
    {
        printf("Create_board failed");
        free(board->error);
        free(board->fixed);
        free(board->arr);
        free(board);
        return NULL;
    }
    board->lst=create_list();
   board->dimension=dimension;board->mark_error=0;board->is_over=0;
board->row_per_block=row_per_block;
board->col_per_block=col_per_block;
board->mode=Init;
return board;
}

void destroy_board(Board* board){
    if(!board)
        return;
    free_lst(board->lst);
    free(board->error);
    free(board->solution);
    free(board->fixed);
    free(board->arr);
    free(board);
}
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){
    int index_row, index_col, index_block, blocks_per_row,num_dash;
    blocks_per_row = dimension / col_per_block;
    num_dash=blocks_per_row*4*col_per_block+1;
    for (index_row = 0; index_row < dimension; index_row++) {
        if (index_row % row_per_block == 0) {
            for(index_block=0; index_block<num_dash; index_block++) {
                printf("-");
            }
            printf("\n");
        }
        for (index_block = 0; index_block < blocks_per_row; index_block++) {
            printf("| ");
            for (index_col = 0; index_col < col_per_block; index_col++) {
                if (arr[index_row][index_col + col_per_block * index_block] != 0) {

                    if (fixed[index_row][index_col + col_per_block * index_block] != 0)
                        printf(" %2d.", arr[index_row][index_col + col_per_block * index_block]);
                    else if(error[index_row][index_col + col_per_block * index_block] != 0){
                    printf(" %2d*", arr[index_row][index_col + col_per_block * index_block]);
                    }
                    else
                        printf("%2d ", arr[index_row][index_col + col_per_block * index_block]);
                } else {
                    printf("   ");
                }
            }
        }
        printf("|\n");
    }
    printf("----------------------------------\n");
}

//||lst->curr->prev==NULL

void undo(int **arr,List *lst){
    int temp;
    if(lst->curr==NULL){
        printf("Can't undo");
        return;
    } else{
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;
        lst->curr=lst->curr->prev;
    }
}

void redo(int **arr,List *lst) {
    int temp;
    if(lst->curr==NULL){
        if(lst->head==NULL) {
            printf("Can't redo");
            return;
        }
        lst->curr=lst->head;
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;

    } else{
    if(lst->curr->next==NULL){printf("Can't redo");return;}
    lst->curr=lst->curr->next;
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;

    }
}

