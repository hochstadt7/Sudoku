#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include <string.h>
#include "ValidBoard.h"
#include "MainAux.h"
#define DELIMITER " \t\r\n"

/*check wether fixed cells are legal in solve mode*/
int fixed_are_valid(int **arr,int **fixed,int dimension,int row_per_block,int col_per_block){
    int row,col;
    int **temp=first_init(dimension);
for(row=0; row<dimension; row++){
    for(col=0; col<dimension; col++){
    if(fixed[row][col]==1){
        if(!is_valid(temp,dimension,row,col,arr[row][col],row_per_block,col_per_block)){
            printf("Fixed cells are not legal in solve mode");
            return 0;
        }
        temp[row][col]=arr[row][col];
    }
    }
}
free(temp);
    return 1;
}

Board* un_format(FILE *dest){
    printf("File isn't in correct form\n");
    fclose(dest);
    return NULL;
}

int is_ok(const char *fix){//fixed=2 not fixed=1 not legal=0
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
    if(index==3&&(fixed==0||fix[index]!='\0'))//3 digits, no dot or to long
        return 0;
    if(fixed==0)
        return 1;
    else
        return 2;
}

Board* load(char *link) {

    /*read dimensions*/
    FILE *dest = NULL;
    char input[125], *num = NULL,stam[125];
    int index, dimension, row_for_block, col_for_block, loop,is_num,is_legal;
    Board *new;
    dest = fopen(link, "r");
    if (dest == NULL) {
        printf("File wasn't opened");
        return NULL;
    }
    /*read dimensions*/
    fgets(input, 10, dest);
    num = strtok(input, DELIMITER);
    if(num==NULL||is_ok(num)!=1)
        return un_format(dest);
    row_for_block = strtol(num, NULL, 10);
    num = strtok(NULL, DELIMITER);
    if(num==NULL||is_ok(num)!=1)
        return un_format(dest);
    col_for_block = strtol(num, NULL, 10);
    num = strtok(NULL, DELIMITER);
    if(num!=NULL)//too many arguments at first row
        return un_format(dest);
    dimension = row_for_block * col_for_block;
    new = create_board(dimension, row_for_block, col_for_block);
    if(new==NULL){
        return NULL;
    }
    /*read content of board*/
    for (loop = 0; loop < dimension; loop++) {

        do {
            fgets(input, 125, dest);
            num= strtok(input, DELIMITER);
        }while(num==NULL&&!feof(dest));
        for (index = 0; index < dimension; index++) {

            if (num == NULL)//too short input, the excepted length is dimension
            {
                return un_format(dest);
            }
            is_legal = is_ok(num);
            if (is_legal == 0)//not legal
                return un_format(dest);
            else {
                is_num=strtol(num,NULL,10);
                if(is_num>dimension)// too big number
                    return un_format(dest);
                new->arr[loop][index]=is_num;
                if(is_legal==2)//fixed value
                {
                    if(is_num==0)// 0 fixed?? illegal
                        return un_format(dest);
                    new->fixed[loop][index]=1;
                }
            }
            num = strtok(NULL, DELIMITER);
        }
        if (num != NULL) {//too long input
            return un_format(dest);
        }
    }
    if(!feof(dest)) {// still not finish reading, might be illegal
        input[0]='\0';//"empty" buffer
        do {
            fgets(input, 125, dest);
            num = strtok(input, DELIMITER);
        } while (num == NULL&&!feof(dest));
        if (num != NULL) {// Problem if there is one enter. why??
            return un_format(dest);
        }
    }
    fclose(dest);
    // need to add conditions:
    // 1. in solve mode- need to check that fixed cells are legal (code is ready above)
    if(!fixed_are_valid(new->arr,new->fixed,new->dimension,new->row_per_block,new->col_per_block))
        return un_format(dest);
    return new;
}
