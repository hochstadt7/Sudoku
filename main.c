#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "Game.h"
#include "Autofill.h"
#include "MainAux.h"
#include "Generate.h"
#include "Solve.h"

/* the main module contains the the game loop - it repeatedly asks the user for input
 * via the parser module, and executes it*/
int main() {
    Board *game = create_board(1, 1, 1);
    struct Command currCommandObj = {
            INVALID, {0}, "", 0.0f, 0
    };
    struct Command *currCommand = &currCommandObj;
    int commandType;
    char str[MAX_COMMAND_LENGTH];
    setbuf(stdout, 0);
    fflush(stdout);
    /* run the game */
    printf("Welcome, we hope you enjoy our sudoku game. Please input a command\n");
    while (1) {
        get_next_command(game->mode, currCommand);
        commandType = get_move_type(currCommand);
        /*no idea why this is necessary, but the string param gets corrupted otherwise*/
        if(currCommand->str_param == NULL)
            str[0]='\0';
        else
            strcpy(str, currCommand->str_param);
        if (get_move_type(currCommand) == 0) {
            continue;
        }
        switch (commandType) {
            case SOLVE:
                game=solve(str, game);
                break;
            case EDIT:
                game=edit(str, game);
                break;
            case MARK_ERRORS:
                setMarkErrors(currCommand->bool_param, game);
                break;
            case PRINT_BOARD:
                print_board(game);
                break;
            case SET:
                /* x/y switch is deliberate*/
                set(currCommand->int_params[1], currCommand->int_params[0], currCommand->int_params[2], game);
                break;
            case VALIDATE:
                validate(game);
                break;
            case GUESS:
                guess(currCommand->float_param, game);
                break;
            case GENERATE:
                generate(currCommand->int_params[0], currCommand->int_params[1], game);
                break;
            case UNDO:
                undo(game);
                break;
            case REDO:
                redo(game);
                break;
            case SAVE:
                save(str, game);
                break;
            case HINT:
                hint(currCommand->int_params[1], currCommand->int_params[0], game);
                break;
            case GUESSHINT:
                guesshint(currCommand->int_params[1], currCommand->int_params[0], game);
                break;
            case NUMSOLUTIONS:
                deter_solve(game->arr, game->error, game->dimension, game->row_per_block, game->col_per_block);
                break;
            case AUTOFILL:
                autofill(game);
                break;
            case RESET:
                reset_list(game);
                break;
            case EXIT:
                exit_game(game);
                return 0;
                break;
            case INVALID:
            default:
                break;
        }
        if(game->mode == SolveMode && !there_are_x_empty(game->arr, game->dimension, 1)){
            print_board(game);
            if(is_erroneous(game->error,game->dimension))
            {
                printf("The solutions contains errors.\n");
            }
            if(!is_erroneous(game->error,game->dimension))
            {
                printf("Puzzle completed successfully.\n");
                game->mode=InitMode;
            }
        }
    }
    return 0;
}
