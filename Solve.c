//
// Created by LENOVO on 02/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "Solve.h"
#include "ValidBoard.h"
#include "Stack.h"

int deter_solve(int **solution, int dimension, int row_per_block, int col_per_block){
    int row, col,num;
    Stack *stk=create_stack();
    Move *mov;
    for (row = 0; row < dimension; row++) {
        for (col = 0; col <dimension; col++) {
            if (solution[row][col] == 0) {
                for (num = 1; num <= dimension; num++) {
                    if (is_valid(solution,dimension,row, col, num,row_per_block,col_per_block)) {
                        solution[row][col] = num;
                        push(stk,row,col,num);
                        break;
                    } else{
                        mov=top(stk);
                        solution[mov->row][mov->col]=0;
                    }

                }
                pop(stk);
                if(is_empty(stk)) {
                    return 0;
                }

            }
        }
    }

    return 1;
}