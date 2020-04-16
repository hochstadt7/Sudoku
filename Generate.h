//
// Created by LENOVO on 24/03/2020.
//

#ifndef BIGPROJECT_GENERATE_H
#define BIGPROJECT_GENERATE_H
void generate(int x,int y,int **arr,int **error,int dimension,int row_per_block,int col_per_block);
int fill_x_cells(int **arr,int dimesnion,int x,int count_empty,int row_per_block,int col_per_block);
int keep_y_cells(int **arr,int dimension,int y);
#endif //BIGPROJECT_GENERATE_H
