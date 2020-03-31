//
// Created by LENOVO on 30/03/2020.
//

#include "Autofill.h"
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "ValidBoard.h"
#include "MainAux.h"

//assumption:curr->next isnt null (curr himself can be null, but than head isnt null, this is because this method always come after successfull undo (in autofill)
/*void remove_next(List *lst){
    Node *tmp;
    if(!lst->curr){//need to remove head
        tmp=lst->head;
        lst->head=lst->head->next;
    }
    else{//need to remove curr->next
        tmp=lst->curr->next;
        lst->curr->next=lst->curr->next->next;
        lst->curr->next->prev=lst->curr;
    }
    free(tmp);
}*/

void autofill(int **arr, int **fixed, int **error, int dimension, int row_per_block, int col_per_block, List *lst) {
    int row, col, num, count, candidate = 0;
    int **temp;
    if (is_errorneous(error, dimension)) {
        printf("Can't autofill errorneous board.\n");
        return;
    }
    temp=first_init(dimension);
    /*if(!temp)
        return;*/
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (arr[row][col] == 0) {
                count = 0;
                for (num = 1; num < dimension + 1; num++) {
                    if (is_valid(arr, dimension, row, col, num, row_per_block, col_per_block)) {
                        count++;
                        candidate = num;
                    }
                }
                if (count == 1) {
                    temp[row][col] = candidate;
                }
            }
        }
    }
    count=0; //now will count successfull adds
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (temp[row][col] != 0) {
                candidate = temp[row][col];
              /*  if(!add(lst, row, col, arr[row][col]))
                {
                    printf("Look at autofill-wrong alloc case wasnt took care yet\n");
                    for(num=0; num<count; num++){
                        undo(arr,lst);
                        remove_next(lst);
                    }
                    free_arrays(temp,dimension);
                    exit(0);
                }*/
                count++;
                arr[row][col] = candidate;//add to memory?
                fix_error(arr, error, dimension, row, col, candidate, row - row % row_per_block,
                          col - col % col_per_block, row_per_block, col_per_block);
            }
        }
    }
    free_arrays(temp,dimension);
    print_board(arr, fixed, error, dimension, row_per_block, col_per_block);
}