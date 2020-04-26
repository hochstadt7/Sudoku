#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include <string.h>
#include "ValidBoard.h"
#include "MainAux.h"
#define NUM 20
#define DELIMITER " \t\r\n"


int fixed_are_valid(int **arr,int **fixed,int dimension,int row_per_block,int col_per_block){
    int row,col;
    int **temp=first_init(dimension);
    /*if(!temp)
        exit(0);*/
    for(row=0; row<dimension; row++){
        for(col=0; col<dimension; col++){
            if(fixed[row][col]==1){
                if(!is_valid(temp,dimension,row,col,arr[row][col],row_per_block,col_per_block)){
                    printf("Fixed cells are not legal in solve mode.\n");
                    return 0;
                }
                temp[row][col]=arr[row][col];
            }
        }
    }
    free_arrays(temp, dimension);
    return 1;
}

Board* un_format(FILE *dest){
    printf("File isn't in correct form.\n");
    fclose(dest);
    return NULL;
}
/*check whether the cell has legal value*/
int is_ok(const char *fix){/*fixed=2 not fixed=1 not legal=0*/
    /*if(fix==NULL) if i get a failure on given file load, try to turn on this two rows maybe it will help
        return 0;*/
    int index=1,fixed=0;
    if(!('0'<=fix[0]&&fix[0]<='9'))
        return  0;
    while (fix[index]!='\0'&&index<3){
        if(fixed==1)
            return 0;
        if(!(('0'<=fix[index]&&fix[index]<='9')||fix[index]=='.'))
            return 0;
        if(fix[index]=='.')
            fixed=1;
        index++;
    }
    if(index==3&&(fixed==0||fix[index]!='\0'))
        return 0;
    if(fixed==0)
        return 1;
    else
        return 2;
}

/*load a new board based on the file input*/
Board* load(char *link,enum gameMode mode) {
    /*read dimensions*/
    FILE *dest = NULL;
    int  dimension, row_for_block, col_for_block, range;
    Board *new;


    char b[NUM];
    int count=0,is_leg,kelet,read=1;
    dest = fopen(link, "r");
    if (dest == NULL) {
        printf("File wasn't opened.\n");
        return NULL;
    }
    /*dimensions*/
    range=fscanf(dest,"%s",b);
    if(range==-1||is_ok(b)!=1)
        return un_format(dest);
    row_for_block = strtol(b, NULL, 10);
    if (row_for_block < 1)/*illegal dimension*/
        return un_format(dest);
    range=fscanf(dest,"%s",b);
    if(range==-1||is_ok(b)!=1)
        return un_format(dest);
    col_for_block = strtol(b, NULL, 10);
    if (row_for_block < 1)/*illegal dimension*/
        return un_format(dest);

    dimension = row_for_block * col_for_block;
    range=dimension*dimension;
    new = create_board(dimension, row_for_block, col_for_block);
    while (count<range){
        read=fscanf(dest,"%s",b);
        if(read==-1)
            break;
        is_leg = is_ok(b);
        if (is_leg == 0)/*not legal*/
            return un_format(dest);
        else {
            kelet=strtol(b,NULL,10);
            if(kelet>dimension)/*too big number*/
                return un_format(dest);
            new->arr[count/dimension][(count%dimension)]=kelet;
            if(is_leg==2)/*fixed value*/
            {
                if(kelet==0)
                    return un_format(dest);
                new->fixed[count/dimension][(count%dimension)]=1;
            }
        }
        count+=1;
    }
    if(count<range||fscanf(dest,"%s",b)!=-1)
        return un_format(dest);
    fclose(dest);
    if(mode==SolveMode&&!fixed_are_valid(new->arr,new->fixed,new->dimension,new->row_per_block,new->col_per_block))
        return un_format(dest);
    return new;


}
