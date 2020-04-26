#ifndef BIGPROJECT_ILP_H
#define BIGPROJECT_ILP_H
#include "Board.h"

/*the ILP module deals with all Linear Programming related tasks*/
/*it contains one main functions - calc(), which assembles and solves a linear model based on the provided board
 *as well as a few helper functions, and interface functions that translate the variable assignments into the requested data*/
enum LPMode {BinaryVars=1, ContinuousVars=2};
/*this struct is used to pass data about the result of the linear program back to the interface functions*/
typedef struct response{
    double * solution; /* some valid assignment if one was found */
    int valid; /* 1 if a feasible solution was found */
}Response;
void guessHintLP(Board *b, int x, int y);/*used for the guesshint action*/
int hintLP(Board *b, int x, int y);/*used for the hint action*/
void guessLP(Board *b, double threshold);/*used for the guess action*/
void generateLP(Board *b, int **resArr, int *valid);/*used for the generate action*/
int validateLP(Board *b);/*used for the validate action*/
Response* calc(Board *src, enum LPMode mode);/*creates and runs a linear program*/

#endif /*BIGPROJECT_ILP_H*/
