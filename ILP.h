#ifndef BIGPROJECT_ILP_H
#define BIGPROJECT_ILP_H
#include "Board.h"

enum LPMode {BinaryVars=1, ContinuousVars=2};

typedef struct response{
    double * solution; /* some valid assignment if one was found */
    int ** cellMap;
    int success; /* 1 if some error occurred */
    int valid; /* 1 if a feasible solution was found */
}Response;
void guessHintLP(Board *b, int x, int y);
int hintLP(Board *b, int x, int y);
void guessLP(Board *b, double threshold);
void generateLP(Board *b, int **resArr, int *valid);
int validateLP(Board *b);
Response* calc(Board *src, enum LPMode mode);

#endif /*BIGPROJECT_ILP_H*/
