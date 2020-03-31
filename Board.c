#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "MainAux.h"


List *create_list() {
    List *tmp = (List *) malloc(sizeof(List));
    if(tmp==NULL){
        printf("List allocation failed.\n");
        exit(0);
    }
    tmp->head = NULL;
    tmp->curr = NULL;
    return tmp;
}
Node* create_node(int row, int col,int val){
    Node *temp= (Node *) malloc(sizeof(Node));
    if(temp==NULL) {
        printf("Node allocation failed");
        exit(0);
    }
    temp->row=row;temp->col=col;temp->val=val;
    temp->next=NULL;temp->prev=NULL;
    return temp;
}

/*add move to the move's list*/
Node* add(List* lst,int row,int col,int val){
    Node *tmp;
    Node* node=create_node(row,col,val);
    /*if(node==NULL) {
        printf("Node allocation has failed.\n");
        exit(0);//need acctually to end the game!?
    }*/
    if(lst->head==NULL){
        lst->head=node;
        lst->curr=node;
    }
    else{
        if(lst->curr!=NULL) {// maybe curr is null!
            tmp = lst->curr->next;
            if (tmp != NULL) {//the redo part of the list is cleared
                while (tmp->next != NULL) {
                    tmp = tmp->next;
                    free(tmp->prev);
                }
                free(tmp);
            }

            lst->curr->next = node;
            node->prev = lst->curr;
            lst->curr = lst->curr->next;
        }
        else{
        tmp=lst->head;
            if (tmp != NULL) {//the redo part of the list is cleared
                while (tmp->next != NULL) {
                    tmp = tmp->next;
                    free(tmp->prev);
                }
                free(tmp);
            }
            lst->head=node;
            lst->curr=node;
        }
    }
    return node;
}


/*undo all moves*/
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
/*free list resources*/
void free_lst(List *lst){
    if(lst->head==NULL)
    {
        free(lst);
        return;
    }

    while (lst->head->next!=NULL) {
        lst->head = lst->head->next;
        free(lst->head->prev);
    }
    free(lst->head);
    free(lst);
}
void print_list(List *lst) {
    Node *tmp = lst->head;
    while (tmp != NULL) {
        printf("row=%d col=%d value=%d.\n", tmp->row, tmp->col,tmp->val);
        tmp = tmp->next;
    }
}
/*create board based on the given parameters*/
Board* create_board(int dimension,int row_per_block,int col_per_block){
Board* board=(Board*) malloc(sizeof(Board));
if(!board) {
    printf("Create_board failed.\n");
    exit(0);
}
board->arr=first_init(dimension);
/*if(board->arr==NULL) {
    printf("Create_board failed.\n");
    free(board);
    exit(0);
}*/
board->fixed=first_init(dimension);
/*if(board->fixed==NULL)
{
    printf("Create_board failed.\n");
    free_arrays(board->arr,board->dimension);
    free(board);
    exit(0);
}*/
board->solution=first_init(dimension);
  /*  if(board->solution==NULL)
    {
        printf("Create_board failed.\n");
        free_arrays(board->fixed,board->dimension);
        free_arrays(board->arr,board->dimension);
        free(board);
        exit(0);
    }*/
    board->error=first_init(dimension);
   /* if(board->error==NULL)
    {
        printf("Create_board failed.\n");
       free_arrays(board->solution,board->dimension);
        free_arrays(board->fixed,board->dimension);
        free_arrays(board->arr,board->dimension);
        free(board);
        exit(0);
    }*/
    board->lst=create_list();
   /* if(board->lst==NULL)
    {
        printf("Create_board failed.\n");
        free_arrays(board->error,board->dimension);
        free_arrays(board->solution,board->dimension);
        free_arrays(board->fixed,board->dimension);
        free_arrays(board->arr,board->dimension);
        free(board);
        exit(0);
    }*/
   board->dimension=dimension;board->mark_error=0;board->is_over=0;
board->row_per_block=row_per_block;
board->col_per_block=col_per_block;
board->mode=Init;
return board;
}
/*free all board resources*/
void destroy_board(Board* board){
    if(!board)
        return;
    free_lst(board->lst);
    free_arrays(board->error,board->dimension);
    free_arrays(board->solution,board->dimension);
    free_arrays(board->fixed,board->dimension);
    free_arrays(board->arr,board->dimension);
    free(board);
}
/*printing the board according to the specified format*/
void print_board(int **arr,int **fixed,int **error,int dimension,int row_per_block,int col_per_block){
    int index_row, index_col, index_block, blocks_per_row,num_dash;
    blocks_per_row = dimension /col_per_block;
    num_dash=4*dimension+row_per_block+1;
    for (index_row = 0; index_row < dimension; index_row++) {
        if (index_row % row_per_block == 0) {
            for(index_block=0; index_block<num_dash; index_block++) {
                printf("-");
            }
            printf("\n");
        }
        for (index_block = 0; index_block < blocks_per_row; index_block++) {
            printf("|");
            for (index_col = 0; index_col < col_per_block; index_col++) {
                if (arr[index_row][index_col + col_per_block * index_block] != 0) {

                    if (fixed[index_row][index_col + col_per_block * index_block] != 0)//fixed cell
                        printf(" %2d.", arr[index_row][index_col + col_per_block * index_block]);
                    else if(error[index_row][index_col + col_per_block * index_block] != 0){//add condition-mode is solve
                    printf(" %2d*", arr[index_row][index_col + col_per_block * index_block]);
                    }
                    else
                        printf(" %2d ", arr[index_row][index_col + col_per_block * index_block]);
                } else {
                    printf("    ");
                }
            }
        }
        printf("|\n");
    }
    for(index_block=0; index_block<num_dash; index_block++) {
        printf("-");
    }
    //printf("\n");
}
/*undo move*/
void undo(int **arr,List *lst){
    int temp;

    if(lst->curr==NULL){//no move to undo
        printf("Can't undo.\n");
        return;
    } else{
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;
        lst->curr=lst->curr->prev;// may be null

    }
}
/*redo move*/
void redo(int **arr,List *lst) {
    int temp;
    if(lst->curr==NULL){
        if(lst->head==NULL) {//no move to redo
            printf("Can't redo.\n");
            return;
        }
        lst->curr=lst->head;
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;

    } else{
    if(lst->curr->next==NULL){printf("Can't redo.\n");return;}
    lst->curr=lst->curr->next;
        temp=arr[lst->curr->row][lst->curr->col];
        arr[lst->curr->row][lst->curr->col]=lst->curr->val;
        printf("Block in row %d, column %d was set to %d.\n",lst->curr->row,lst->curr->col,lst->curr->val);
        lst->curr->val=temp;

    }
}

