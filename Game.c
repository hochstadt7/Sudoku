#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Board.h"
#include <string.h>


void hint(int **solution, int y, int x) {
    printf("Hint: set cell to %d\n", solution[x][y]);
}



void save(char *link,Board *board){
FILE *dest=NULL;
dest=fopen(link,"w");
if(dest==NULL)
{
    printf("Error in save");
    exit(0);
}
fprintf(dest,"%d %d\n",board->row_per_block,board->col_per_block);
    int index_row, index_col;
    for (index_row = 0; index_row < board->dimension; index_row++) {

        for (index_col = 0; index_col < board->dimension; index_col++) {
                if(board->fixed[index_row][index_col]!=1)
                {
                    fprintf(dest,"%d ",board->arr[index_row][index_col]);
                }
                else {
                    fprintf(dest,"%d. ",board->arr[index_row][index_col]);
                }

        }
        fprintf(dest,"\n");
    }
    fclose(dest);
}



