#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Board.h"
#include "MainAux.h"
#include "Parser.h"
#include "FileManager.h"
#include "ValidBoard.h"
#include "Solve.h"
#include "Stack.h"
#include "TestGame.h"
#define DIMENSION 9
#define ROWPERBLOCK 3
#define COLPERBLOCK 3
//#include "History.h"


int main() {
    int is_over=0;
    struct Command *currCommand;
    int commandType;
    int *params;
    int **arr, **fixed, **solution;
    time_t t;
    setbuf(stdout, 0);
    arr = first_init(DIMENSION);
    fixed = first_init(DIMENSION);
    solution = first_init(DIMENSION);

    initialize(arr, fixed, solution, DIMENSION, ROWPERBLOCK, COLPERBLOCK);
    /* run the game */
    while (1) {
        currCommand = get_next_command(is_over);
        commandType = get_move_type(currCommand);
        if (get_move_type(currCommand) == 0) {
            continue;
        }
        switch (commandType) {
            case SOLVE:
                break;
            case EDIT:
                break;
            case MARK_ERRORS:
                break;
            case PRINT_BOARD:
                break;
            case SET:
                break;
            case VALIDATE:
                break;
            case GUESS:
                break;
            case GENERATE:
                break;
            case UNDO:
                break;
            case REDO:
                break;
            case SAVE:
                break;
            case HINT:
                break;
            case GUESSHINT:
                break;
            case NUMSOLUTIONS:
                break;
            case AUTOFILL:
                break;
            case RESET:
                break;
            case EXIT:
                break;
            case INVALID:
            default:
                break;
        }
        return 0;
    }
    return 0;
}