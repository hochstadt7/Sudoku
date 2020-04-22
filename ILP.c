#include "ILP.h"
#include "Board.h"
#include "Autofill.h"
#include "ValidBoard.h"
#include "MainAux.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define GUROBI 0
#if GUROBI

#include "gurobi_c.h"

#endif

Board *get_autofilled(Board *b) {
    int **arr;
    int dimension, row_per_block, col_per_block;
    int row, col, num, count, candidate = 0;
    Board *temp;
    dimension = b->dimension;
    row_per_block = b->row_per_block;
    col_per_block = b->col_per_block;
    arr = b->arr;
    temp=duplicateBoard(b);
    for (row = 0; row < dimension; row++) {
        for (col = 0; col < dimension; col++) {
            if (arr[row][col] == 0) {
                count = 0;
                for (num = 1; num < dimension + 1; num++) {
                    if (is_valid(arr,dimension,row,col,arr[row][col],row_per_block,col_per_block)) {
                        count++;
                        candidate = num;
                    }
                }
                if (count == 1) {
                    temp->arr[row][col] = candidate;
                }
            }
        }
    }
    return temp;
}


#if GUROBI

void freeTemporaryArrays(int *ind, double *val, int ***rowVars, int ***colVars, int ***blockVars, int **cellVars,
                         char *vType, double *solution, int dimension) {
    int i, j;
    free(ind);
    free(val);
    free(vType);
    free(solution);
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            free(cellVars[(dimension * i) + j]);
            free(rowVars[i][j]);
            free(blockVars[i][j]);
            free(rowVars[i][j]);
        }
        free(rowVars[i]);
        free(blockVars[i]);
        free(rowVars[i]);
    }
    free(rowVars);
    free(colVars);
    free(blockVars);
    free(cellVars);
}

Response *QUIT(GRBmodel *model, GRBenv *env, int error, Board *b, int status,
               int *ind, double *val, int ***rowVars, int ***colVars, int ***blockVars, int **cellVars, char *vType, double *solution,
               int dimension) {
    Response *res = (Response *) malloc(sizeof(Response));
    if (error) {
        printf("ERROR: %s\n code: %d\n", GRBgeterrormsg(env), error);
        exit(1);
    }
    /* Free model */
    GRBfreemodel(model);

    /* Free environment */
    GRBfreeenv(env);

    /*release temporary arrays used throughout the program*/
    freeTemporaryArrays(ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    res->solution = b;
    res->valid = (status == GRB_OPTIMAL);
    res->success = (status == GRB_OPTIMAL || status == GRB_INF_OR_UNBD);
    return res;
}

#endif

Response *calc(Board *src) {
#if GUROBI
    GRBenv *env = NULL;
    GRBmodel *model = NULL;
#endif
    int *ind; /* should be of size dimension*dimension*dimension */
    double *val; /* should be of size dimension */
    int ***rowVars; /* indices of variables, indexed by row and value */
    int ***colVars; /* indices of variables, indexed by col and value */
    int ***blockVars; /* indices of variables, indexed by block and value */
    int **cellVars; /* indices of variables, indexed by cell */
#if GUROBI
    char *vType; /* should be of size dimension*dimension*dimension */
    double *solution;
    int optimStatus = -1;
    double objVal;
#endif

    int dimension, blockWidth, blockHeight;
    int i, j, v, blockIndex, indexInBlock, varCount, valueIsValid;
    int temp;
    int varConstraintIndex; /* the index of the currently processed variable within the currently constructed constraint*/
#if GUROBI
    int error = 0;
#endif
    Board *b = get_autofilled(src);
    dimension = b->dimension;
    blockWidth = b->col_per_block;
    blockHeight = b->row_per_block;

    /*array allocation*/
    ind = init_malloc(sizeof(int), (dimension * dimension * dimension), INT);
    val = init_malloc(sizeof(double), (dimension * dimension * dimension), DOUBLE);
    cellVars = init_malloc(sizeof(int *), dimension * dimension, INT_POINTER);
    rowVars = init_malloc(sizeof(int *), dimension, INT_POINTER);
    colVars = init_malloc(sizeof(int *), dimension, INT_POINTER);
    blockVars = init_malloc(sizeof(int *), dimension, INT_POINTER);

#if GUROBI
    vType = malloc(sizeof(char) * (dimension * dimension * dimension));
    solution = malloc(sizeof(double) * (dimension * dimension * dimension));
#endif

    /* Create an empty model */
    varCount = 0;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            /*each cell in the cellVars array contains an array of variables, one for each possible value*/
            cellVars[i * dimension + j] = init_malloc(sizeof(int), dimension, INT);
            blockIndex = (int) (dimension / blockWidth) * (int) (j / blockHeight) + (int) (i / blockWidth);
            indexInBlock = blockWidth * (j % blockHeight) + (i % blockWidth);
            for (v = 0; v < dimension; v++) {
                /*----------------ALLOCATION OF ARRAYS ON DEMAND------------------*/
                if (rowVars[i] == NULL) {
                    rowVars[i] = init_malloc(sizeof(int *), dimension, INT_POINTER);
                }
                if (colVars[j] == NULL) {
                    colVars[j] = init_malloc(sizeof(int *), dimension, INT_POINTER);
                }
                if (blockVars[blockIndex] == NULL) {
                    blockVars[blockIndex] = init_malloc(sizeof(int *), dimension, INT_POINTER);
                }
                if (rowVars[i][v] == NULL) {
                    rowVars[i][v] = init_malloc(sizeof(int), dimension, INT);
                }
                if (colVars[j][v] == NULL) {
                    colVars[j][v] = init_malloc(sizeof(int), dimension, INT);
                }
                if (blockVars[blockIndex][v] == NULL) {
                    blockVars[blockIndex][v] = init_malloc(sizeof(int), dimension, INT);
                }
                /*----------------ALLOCATION END------------------*/
                valueIsValid = (!b->arr[i][j]) && is_valid(b->arr, dimension, i, j, v, blockHeight, blockWidth);
                if (valueIsValid) {
                    varCount++;
                    cellVars[i * dimension + j][v] = varCount;
                    rowVars[i][v][j] = varCount;
                    colVars[j][v][i] = varCount;
                    blockVars[blockIndex][v][indexInBlock] = varCount;
                } else {
                    cellVars[i * dimension + j][v] = -1;
                    rowVars[i][v][j] = -1;
                    colVars[j][v][i] = -1;
                    blockVars[blockIndex][v][indexInBlock] = -1;
                }
            }
        }
    }
#if GUROBI
    for (i = 0; i < dimension * dimension * dimension; i++) {
        vType[i] = GRB_BINARY;
    }
    /* Create environment */
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {

        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);

    }

    /* Create new model */
    error = GRBnewmodel(env, &model, "sudoku", varCount, NULL, NULL, NULL, vType, NULL);
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }
#endif
    /*-----------CONSTRAINTS-----------*/
    /* limit cells to one value */
    /* iterate over rows */
    for (i = 0; i < dimension; i++) {
        /* iterate over columns */
        for (j = 0; j < dimension; j++) {
            varConstraintIndex = 0;
            /* iterate over values */
            for (v = 0; v < dimension; v++) {
                if (cellVars[(i * dimension) + j][v] != -1) {
                    ind[varConstraintIndex] = cellVars[i * dimension + j][v];
                    val[varConstraintIndex] = 1.0;
                    varConstraintIndex++;
                }
            }
            for(temp=0; temp<dimension; temp++){
                printf("%d, ", ind[temp]);
            }
            printf("\n");
            printf("Set %d constraints for cell %d, %d\n", varConstraintIndex, i, j);
#if GUROBI
            varConstraintIndex = (varConstraintIndex - 1) < 0 ? 0 : (varConstraintIndex - 1);
            error = GRBaddconstr(model, varConstraintIndex, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
            }
#endif
        }
    }
#if 0
    /* limit each value to one appearance per row */
    /* iterate over rows */
    for (i = 0; i < dimension; i++) {
        /* iterate over values */
        for (v = 0; v < dimension; v++) {
            varConstraintIndex = 0;
            /* iterate over columns */
            for (j = 0; j < dimension; j++) {
                if (rowVars[i][v][j] != -1) {
                    ind[varConstraintIndex] = rowVars[i][v][j];
                    val[varConstraintIndex] = 1.0;
                    varConstraintIndex++;
                }
            }
#if GUROBI
            varConstraintIndex = (varConstraintIndex - 1) < 0 ? 0 : (varConstraintIndex - 1);
            error = GRBaddconstr(model, varConstraintIndex, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
            }
#endif
        }
    }

    /* limit each value to one appearance per col */
    /* iterate over columns */
    for (j = 0; j < dimension; j++) {
        /* iterate over values */
        for (v = 0; v < dimension; v++) {
            varConstraintIndex = 0;
            /* iterate over rows */
            for (i = 0; i < dimension; i++) {
                if (colVars[j][v][i] != -1) {
                    ind[varConstraintIndex] = colVars[j][v][i];
                    val[varConstraintIndex] = 1.0;
                    varConstraintIndex++;
                }
            }
#if GUROBI
            varConstraintIndex = (varConstraintIndex - 1) < 0 ? 0 : (varConstraintIndex - 1);
            error = GRBaddconstr(model, varConstraintIndex, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
            }
#endif
        }
    }

    /* limit each value to one appearance per block */
    /* iterate over blocks */
    for (blockIndex = 0; blockIndex < dimension; blockIndex++) {
        /* iterate over values */
        for (v = 0; v < dimension; v++) {
            varConstraintIndex = 0;
            /* iterate over cells within block */
            for (indexInBlock = 0; indexInBlock < dimension; indexInBlock++) {
                i = (blockWidth * (blockIndex % (dimension / blockWidth))) + (indexInBlock % blockWidth);
                j = (blockHeight * (blockIndex / (dimension / blockWidth))) + (indexInBlock / blockWidth);
                if (blockVars[j][v][i] != -1) {
                    ind[varConstraintIndex] = blockVars[j][v][i];
                    val[varConstraintIndex] = 1.0;
                    varConstraintIndex++;
                }
            }
#if GUROBI
            varConstraintIndex = (varConstraintIndex - 1) < 0 ? 0 : (varConstraintIndex - 1);
            error = GRBaddconstr(model, varConstraintIndex, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
            }
#endif
        }
    }
#endif
#if GUROBI
    /* Optimize model */
    error = GRBoptimize(model);
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }

    /* Write model to 'sudoku.lp' */
    error = GRBwrite(model, "sudoku.lp");
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }

    /* Capture solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimStatus);
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }

    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objVal);
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, varCount, solution);
    if (error) {
        return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
    }

    for (i = 0; i < varCount; i++)
        printf("%d ", (int) solution[i]);

    /* iterate over rows */
    for (i = 0; i < dimension; i++) {
        /* iterate over columns */
        for (j = 0; j < dimension; j++) {
            /* iterate over values */
            temp = 0;
            for (v = 0; v < dimension; v++) {
                if (cellVars[(i * dimension) + j][v] != -1) {
                    if((int) solution[cellVars[(i * dimension) + j][v]]){
                        b->arr[i][j] = v+1;
                        temp++;
                    }
                }
            }
            if(temp>1)
                printf("for some reason cell %d, %d has %d associated values\n", i, j, temp);
        }
    }
    print_board(b);
    return QUIT(model, env, error, b, optimStatus, ind, val, rowVars, colVars, blockVars, cellVars, vType, solution, dimension);
#endif
#if !GUROBI
    return NULL;
#endif
}
