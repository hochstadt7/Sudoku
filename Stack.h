//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_STACK_H
#define BIGPROJECT_STACK_H

typedef struct move{
    int row,col,val;
    struct move *next;
}Move;

typedef struct stack{
    Move *top;
}Stack;

Stack *create_stack();
int is_empty(Stack *memory);
void pop(Stack *memory);
Move* top(Stack *memory);
void push(Stack *memory,int row,int col,int value);
void print_stack(Stack *stk);
void free_stack(Stack *stk);


#endif //BIGPROJECT_STACK_H
