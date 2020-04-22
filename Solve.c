#include <stdio.h>
#include "ValidBoard.h"
#include "Stack.h"
#include "MainAux.h"


int deter_solve(int **solution, int **error, int dimension, int row_per_block, int col_per_block) {
    Stack *stk;
    Move *up;
    int  curr_row,curr_col,found_legal,count=0,is_sol=0;
    int **arr=first_init((dimension));
    /*if(!arr){
        return 0;
    }*/
    if(is_erroneous(error,dimension))/*board is erroneous- no solution*/
    {
        printf("No solution- board is erroneous.\n");
        return 0;
    }
    stk=create_stack();
    /*if(!stk){
        free_arrays(arr,dimension);
        return 0;
    }*/
    for(curr_row=0; curr_row<dimension; curr_row++) {/*index unfilled cells*/
        for (curr_col = 0; curr_col < dimension; curr_col++) {
          if(solution[curr_row][curr_col]!=0)
              arr[curr_row][curr_col]=1;
        }
        }
    push(stk, 0, 0, 0);
    /*if(!push(stk, 0, 0, 0))
    {
        free_arrays(arr,dimension);
        free_stack(stk);
        return 0;
    }*/
    while (!is_empty(stk)) {
        up = stk->top;
        curr_row=up->row;
        curr_col=up->col;
        found_legal=0;

        if(arr[curr_row][curr_col]==0||is_sol==1) {/*if* the block is empty or we found solution just now*/
            is_sol=0;
            while (up->val < dimension) {
                up->val++;

                if (is_valid(solution, dimension, curr_row, curr_col, up->val, row_per_block, col_per_block)) {
                    solution[curr_row][curr_col] = up->val;
                    found_legal = 1;/* legal value was found */
                    break;
                }
            }
        }
        if (found_legal==0&&arr[curr_row][curr_col]==0) {/* no solution to this empty cell */
            solution[curr_row][curr_col] = 0;
            do{
                pop(stk);
            }while (!is_empty(stk)&&arr[stk->top->row][stk->top->col]==1);

        } else {
            if(curr_col==dimension-1){
                if(curr_row==dimension-1)/*solution was found */
                {
                    /*free_stack(stk);
                    return 1;*/
                    
                    count++;
                    if(arr[curr_row][curr_col]==1)
                    {
                        do{
                            pop(stk);
                        }while (!is_empty(stk)&&arr[stk->top->row][stk->top->col]==1);
                    } else{
                      is_sol=1;/*we have found a new solution just now */
                    }
                }
                else{
                    push(stk, curr_row+1, 0, 0);
                   /* if(!push(stk, curr_row+1, 0, 0))//move to the next cell
                    {
                        free_arrays(arr,dimension);
                        free_stack(stk);
                        return 0;
                    }*/

                }
            }
            else{
                push(stk, curr_row, curr_col+1, 0);
               /* if(!push(stk, curr_row, curr_col+1, 0))//backtracking
                {
                    free_arrays(arr,dimension);
                    free_stack(stk);
                    return 0;
                }*/
            }
            }

        }
    free_arrays(arr,dimension);
    free_stack(stk);
    printf("there are %d valid solutions\n", count);
    return count;
}
