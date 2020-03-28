//
// Created by LENOVO on 24/03/2020.
//

#include "Generate.h"
#include <stdio.h>
#include <stdlib.h>
#include "MainAux.h"
#include "board.h"
#include "ValidBoard.h"

/*create node holding row and column numbers*/
Node* create_node(int row, int col){
    Node *temp= (Node *) malloc(sizeof(Node));
    if(temp==NULL) {
        printf("Node allocation failed\n.");
        return NULL;
    }
    temp->row=row;temp->col=col;
    return temp;
}
/*check wether there are x empty cells*/
int there_are_x_empty(int **arr,int dimension){
    int count_empty=0;
    for(row=0; row<dimesnion; row++){
        for (col=0; col<dimesnion; col++) {
            if(arr[row][col]==0)
                count_empty++;
        }
    }
    if(count_empty<x)
        return -1;
    return count_empty;
}
/*randomaly choose legal value for cell in specified row and column*/
int choose_legal(int *arr,int dimension,int row,int col,int row_per_block,int col_per_block){
    int count=0,val;
    int all_nums=dimension**2;
    int *legal=malloc(all_nums* sizeof(int)));
for(val=1; val<all_nums+1; val++){
if(is_valid(arr,dimension,row,col,val,row_per_block,col_per_block)){
  legal[count]=val;
  count++;
}
}
if(count==0){
    free(legal);
    return 0;
    }
count=rand()%count;
count=legal[count];
free(legal);
    return count;
}
/*randomly choose X cells and fill each selected cell with a random legal value */
int fill_x_cells(int **arr,int dimesnion,int x,int count_empty){
    int row,col,random,index=0,legal_val=0;
    Node **cell,*node;
    cell=malloc(count_empty* sizeof(*Node));//not right?
    for(row=0; row<dimesnion; row++){//find all empty cells
        for (col=0; col<dimesnion; col++) {
            if(arr[row][col]==0)
            {
                node=create_node(row,col);
                if(!node)
                {
                    printf("Allocation failed\n.");
                    for(index=0; index<legal_val; index++){
                        free(cell[index]);
                    }
                    free(cell);
                    return 0;
                }
                cell[legal_val]=node;//store node
                legal_val++;
            }
        }
    }
    col=legal_val;//save for the end (free memory)
    count_empty=legal_val;
    for(index=0; index<x; index++){
        random=rand()%count_empty;
        legal_val=choose_legal(arr,dimesnion,cell[random]->row,cell[random]->col);//missing
        if(!legal_val)//no legal value, need to return 0? or just move to next iteration? look at question on moodle
        {
            for(index=0; index<count_empty; index++){//free memory before return
                free(cell[index]);
            }
            free(cell);
            printf("Not solvable board.\n");
            return 0;
        }
        arr[cell[random]->row][cell[random]->col]=legal_val;
        while (random<count_empty-1){//we dont want spaces in cell array of unsued row/col
            cell[random]=cell[random+1];
            random++;
        }
        count_empty--;
    }
    for(index=0; index<col; index++){
        free(cell[index]);
    }
    free(cell);
    return 1;
}
/*randomly choose Y cells out of the entire board and clear the values of all other cells*/
int keep_y_cells(int **arr,int dimension,int y){
    int row,col,random,index,legal_val=0,**temp,free_holder;
    Node **cell,*node;
    cell=malloc((dimension**2) sizeof(*Node));//not right? maybe node* []
for(row=0; row<dimension; row++){
    for(col=0; col<dimension; col++){
        node=create_node(row,col);
        if(!node){
            printf("Allocation failed.\n");
            for(index=0; index<legal_val; index++){
                free(cell[index]);
            }
            free(cell);
            return 0;
        }
        cell[index]=node;//need to check that allocation succeeded
        legal_val++;
    }
}
temp=first_init(dimension);
free_holder=legal_val;
for(row=0; row<y; row++)
{
random=rand()%legal_val;
temp[cell[random]->row][cell[random]->col]=1;
    while (random<legal_val-1){//decrease range for rand()
        cell[random]=cell[random+1];
        random++;
    }
    legal_val--;
}
for(row=0; row<dimension; row++){
    for(col=0; col<dimension; col++){
        arr[row][col]=(temp[row][col]==1?arr[row][col]:0);
    }
}
    for(index=0; index<legal_val; index++){
        free(cell[index]);
    }
    free(cell);
    free(temp);
    return 1;
}
/*Generates a puzzle by randomly filling X empty cells with legal values, running ILP to solve the board, and then clearing all but Y random cells*/
void generate(int x,int y,int **arr,int **error,int dimension,int row_per_block,int col_per_block){
    int iteration=0,**temp,count_empty;
    //findout wether i need to check input or its done in parser (x,y<board size)

    if(is_errorneous(error,dimension)) {
        printf("Errorneous board can't be generated.\n");
        return;
    }
    count_empty=there_are_x_empty(arr,dimension);
    if(count_empty==-1){
        printf("There aren't x empty cells.\n");
        return;
    }
    temp=first_init(dimension);
    while (iteration<1000) {
        copy_arrays(arr,temp);//dont want to change arr itself, unless succeed
        if(!fill_x_cells(temp, dimension,x,count_empty))//failure in allocation/no legal value for some cells
            return;
        if(!ilp(temp)){
            iteration++;
            continue;
        }
        if(!keep_y_cells(temp,dimension))//failure in allocation
            return;
        copy_arrays(temp,arr);
        free_arrays(temp,dimension);
        return;//succsess
    }
    printf("Generation failed.\n");
}