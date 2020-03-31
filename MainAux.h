//
// Created by LENOVO on 02/01/2020.
//

#ifndef BIGPROJECT_MAINAUX_H
#define BIGPROJECT_MAINAUX_H

int** first_init(int dimension);/*initialize board*/
void copy_arrays(int **copy, int**paste,int dimension);/*copy data of copy to paste*/
int is_errorneous(int **error,int dimension);
//void initialize(int **arr,int **fixed,int **solution,int **error,int dimension, int row_per_block,int col_per_block);
void free_arrays(int **arr,int dimension);
#endif //BIGPROJECT_MAINAUX_H
