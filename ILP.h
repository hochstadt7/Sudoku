#ifndef BIGPROJECT_ILP_H
#define BIGPROJECT_ILP_H
#include "Board.h"

enum LPMode {BinaryVars=1, ContinuousVars=2};

typedef struct response{
    Board * solution; /* some valid assignment if one was found */
    int success; /* 1 if some error occurred */
    int valid; /* 1 if a feasible solution was found */
}Response;

Response* calc(Board *src, enum LPMode mode, double threshold);

#endif /*BIGPROJECT_ILP_H*/
