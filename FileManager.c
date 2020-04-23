#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "ValidBoard.h"
#include "MainAux.h"
#define ROW 250
#define DELIMITER " \t\r\n"

int fixed_are_valid(int **arr,int **fixed,int dimension,int row_per_block,int col_per_block){
    int row,col;
    int **temp=first_init(dimension);
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
    free_arrays(temp,dimension);
    return 1;
}

/*prints error if the file's format is incorrect, and cleanup*/
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

int get_rid_row(int dimension,int *loop,Board *new,char **num,int range){
    int is_legal,is_num;
    do {
        is_legal = is_ok(*num);
        if (is_legal == 0)/*not legal*/
            return 0;
        else {
            is_num=strtol(*num,NULL,10);
            if(is_num>dimension)/* too big number*/
                return 0;
            new->arr[*loop/dimension][(*loop%dimension)]=is_num;/* need to fix!!!!!!!!!!!*/
            if(is_legal==2)/*fixed value*/
            {
                if(is_num==0)/* 0 fixed?? illegal*/
                    return 0;
                new->fixed[*loop/dimension][(*loop%dimension)-1]=1;
            }
        }
        *num = strtok(NULL, DELIMITER);
        *loop+=1;
    } while (*num != NULL &&*loop<range);/*get rid of abudants rows*/
    return 1;
}

/*load a new board based on the file input*/
Board* load(char *link, enum gameMode mode) {
    char* a;
    /*read dimensions*/
    FILE *dest = NULL;
    char input[ROW], *num = NULL;
    int  dimension, row_for_block, col_for_block, loop=0,range;
    Board *new;
    dest = fopen(link, "r");
    if (dest == NULL) {
        printf("File wasn't opened.\n");
        return NULL;
        /*exit(0);*/
    }
    /*read dimensions*/
    do {
        fgets(input, ROW, dest);/* is 125 apropriate???????????*/
        num = strtok(input, DELIMITER);
    } while (num == NULL && !feof(dest));/*get rid of abudants rows*/

    /*here i need to fix*/
    if (num == NULL || is_ok(num) != 1)
        return un_format(dest);

    row_for_block = strtol(num, NULL, 10);
    if (row_for_block < 1)/*illegal dimension*/
        return un_format(dest);
    num = strtok(NULL, DELIMITER);
    if (num == NULL) {
        do {
            fgets(input, ROW, dest);/* is 125 apropriate???????????*/
            num = strtok(input, DELIMITER);
        } while (num == NULL && !feof(dest));/*get rid of abudants rows*/

    }
    if (feof(dest) || is_ok(num) != 1){
        return un_format(dest);
    }
    col_for_block=strtol(num, NULL, 10);
    if(col_for_block<1)
        return un_format(dest);


    num = strtok(NULL, DELIMITER);
    dimension = row_for_block * col_for_block;
    range=dimension*dimension;
    new = create_board(dimension, row_for_block, col_for_block);
    if(num!=NULL)/*get rid of row content*/
    {

        if(get_rid_row(dimension,&loop,new,&num,range)==0||num!=NULL)
            return un_format(dest);

    }

    /*read content of board*/
    while (!feof(dest)&&loop<range){
        do {
            a = fgets(input, ROW, dest);/* is 125 apropriate???????????*/
            num = strtok(input, DELIMITER);
        } while (num == NULL && (!feof(dest)));/*get rid of abudants rows*/

        if(get_rid_row(dimension,&loop,new,&num,range)==0||num!=NULL||a==NULL)
            return un_format(dest);
    }
    /*finish*/
    if(loop<range) /*we existed while because of feof*/
        return un_format(dest);
    if(!feof(dest)) { /* still not finish reading, might be illegal*/
        input[0]='\0'; /*"empty" buffer*/
        do {
            fgets(input, ROW, dest);
            num = strtok(input, DELIMITER);
        } while (num == NULL&&!feof(dest));
        if (num != NULL) {/* Problem if there is one enter. why??*/
            return un_format(dest);
        }
    }
    fclose(dest);
    /* need to add conditions:*/
    /* 1. in solve mode- need to check that fixed cells are legal (code is ready above)*/
    if(mode==SolveMode&&!fixed_are_valid(new->arr,new->fixed,new->dimension,new->row_per_block,new->col_per_block))
        return un_format(dest);
    return new;
}
