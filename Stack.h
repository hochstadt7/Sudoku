//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_STACK_H
#define BIGPROJECT_STACK_H

/*holder of move*/
typedef struct move{
    int row,col,val;
    struct move *next;
}Move;

/*stack holds the moves*/
typedef struct stack{
    Move *top;
}Stack;

Stack *create_stack();/*create the stack which holds moves*/
int is_empty(Stack *memory);/*return whether stack is empty*/
void pop(Stack *memory);/*pop last move inserted to stack*/
Move *create_move(int row,int col,int value);
Move* top(Stack *memory);/*look at last move inserted to stack*/
Move* push(Stack *memory,int row,int col,int value);/*insert move to stack,represented by row,column and value*/
void print_stack(Stack *stk);
void free_stack(Stack *stk);/*free memory of stack*/


#endif //BIGPROJECT_STACK_H
