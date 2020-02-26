//
// Created by LENOVO on 08/01/2020.
//
/* validation of value in row */
int in_row(const int *arr, int dimension, int value) {
    int index;
    for (index = 0; index < dimension; index++) {
        if (arr[index] == value)
            return 1;
    }
    return 0;
}
/* validation of value in column */
int in_col(int **arr, int dimension, int col, int value) {
    int index;
    for (index = 0; index < dimension; index++) {
        if (arr[index][col] == value)
            return 1;
    }

    return 0;
}
/* validation of value in block */
int in_block(int **arr, int block_start_row, int block_start_col, int value, int row_per_block,
             int col_per_block) {
    int row, col;
    for (row = 0; row < row_per_block; row++) {
        for (col = 0; col < col_per_block; col++) {
            if (arr[row + block_start_row][col + block_start_col] == value)
            {
                return 1;
            }
        }
    }
    return 0;
}
/*check if requested assignment is legal*/
int is_valid(int **arr, int dimension, int row, int col, int value, int row_per_block, int col_per_block) {
    if (arr[row][col] == value) {
        return 1;
    }
    if ((in_block(arr, row - row % row_per_block, col - col % col_per_block, value,row_per_block,col_per_block) || (in_row(arr[row],dimension,value)) || (in_col(arr,dimension, col, value)))) {
        return 0;
    }
    return 1;
}
/*set errorneous board values*/
void fix_error(int **arr,int **error,int dimension,int row,int col,int value, int block_start_row, int block_start_col,int row_per_block,int col_per_block){
    int index,add_or_remove;
    add_or_remove=value==0?0:1;
    for (index = 0; index < dimension; index++) {
        if (arr[row][index] == arr[row][col]){error[row][index]=add_or_remove;}
    }
    for (index = 0; index < dimension; index++) {
        if (arr[index][col] == arr[row][col]){error[row][index]=add_or_remove;}
    }
    for (row = 0; row < row_per_block; row++) {
        for (col = 0; col < col_per_block; col++) {
            if (arr[row + block_start_row][col + block_start_col] == arr[row][col]){error[row][index]=add_or_remove;}
        }
    }
}