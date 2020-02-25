//
// Created by LENOVO on 02/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "Solve.h"
#include "ValidBoard.h"
#include "Stack.h"
#include "MainAux.h"

/*find next empty block*/
/*int *find_next_empty(int **arr, int dimension,int row,int col){
    int i=0,j=0;
    int *ret=malloc(2* sizeof(int));
   for(i=row; i<dimension; i++) {
       for(j=0; j<dimension; j++)
       {
           if(!(i==row&&j<=col)) {
               if (arr[i][j] != 1) {
                   ret[0] = i;
                   ret[1] = j;
                   return ret;
               }
           }
       }
   }
   ret[0]=-1;
   ret[1]=-1;
    return ret;

}*/

/*count number of possible solutions for the given board*/
int deter_solve(int **solution, int dimension, int row_per_block, int col_per_block) {

    Stack *stk = create_stack();
    Move *up;
    int  curr_row,curr_col,found_legal,count=0;
    int **arr=first_init((dimension));//index unfilled blocks
    for(curr_row=0; curr_row<dimension; curr_row++) {
        for (curr_col = 0; curr_col < dimension; curr_col++) {
          if(solution[curr_row][curr_col]!=0)
              arr[curr_row][curr_col]=1;
        }
        }

    push(stk, 0, 0, 0);
    while (!is_empty(stk)) {
        up = stk->top;
        curr_row=up->row;
        curr_col=up->col;
        found_legal=0;
        if(arr[curr_row][curr_col]==0) {//if the block is empty
            while (up->val < dimension) {
                up->val++;

                if (is_valid(solution, dimension, curr_row, curr_col, up->val, row_per_block, col_per_block)) {
                    solution[curr_row][curr_col] = up->val;
                    found_legal = 1;
                    break;
                }
            }
        }
        if (found_legal==0&&arr[curr_row][curr_col]==0) {// no solution to this empty block
            solution[curr_row][curr_col] = 0;
            do{
                pop(stk);
            }while (!is_empty(stk)&&arr[stk->top->row][stk->top->col]==1);

        } else {
            if(curr_col==dimension-1){
                if(curr_row==dimension-1)//solution was found
                {
                    /*free_stack(stk);
                    return 1;*/
                    count++;
                }
                else{
                    push(stk, curr_row+1, 0, 0);
                }
            }
            else{
                push(stk, curr_row, curr_col+1, 0);
            }
            }

        }
    free_stack(stk);
    return count;
}

