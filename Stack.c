#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

/*the solve module contains the implementation of the stack-based exhaustive backtracking algorithm*/
Move *create_move(int row,int col,int value){
Move *temp=(Move*)malloc(sizeof(Move));
if(!temp) {
    printf("Move alloc failed.\n");
    return NULL;
}
temp->row=row;
temp->col=col;
temp->val=value;
temp->next=NULL;
return temp;
}

Stack* create_stack(){
    Stack *tmp=(Stack*)malloc(sizeof(Stack));
    if(!tmp){
        printf("Stack allocation failed.\n");
        return NULL;
    }
    tmp->top=NULL;
    return tmp;
}

int is_empty(Stack *memory){
    return  memory->top==NULL;
}

void pop(Stack *memory){

    Move *temp=memory->top;
    memory->top=memory->top->next;
    free(temp);
}

Move* top(Stack *memory){

    return memory->top;
}

Move* push(Stack *memory,int row,int col,int value) {
    Move *new = create_move(row, col, value);
    if (!new){
        printf("Stack allocation failed.\n");
        return NULL;
    }

    if (!memory->top){
        memory->top = new;
} else{
        Move *temp=memory->top;
        memory->top=new;
        new->next=temp;
    }
    return new;
}

void print_stack(Stack *stk){
    Move *mov=(stk)->top;
    while (mov!=NULL){
        printf("row=%d col=%d.\n",mov->row,mov->col);
        mov=mov->next;
    }
}
void free_stack(Stack *stk){
    while (stk->top!=NULL){
        pop(stk);
    }
    free(stk);
}


