#include <stdio.h>
#include "Parser.h"
#include "Game.h"
#include "ValidBoard.h"
#include "Autofill.h"
#include "ILP.h"
#include "Generate.h"

void print_me(int **arr,int dimension)
{
    int index_row,index_col;
    for(index_row=0; index_row<dimension; index_row++){
        for(index_col=0; index_col<dimension; index_col++)
        {
            printf("%d ",arr[index_row][index_col]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main() {
    Board *game = create_board(1, 1, 1);
    struct Command *currCommand;
    int commandType;
    /* run the game */
    while (1) {
        currCommand = get_next_command(game->mode);
        commandType = get_move_type(currCommand);
        if (get_move_type(currCommand) == 0) {
            continue;
        }
        switch (commandType) {
            case SOLVE:
                solve(currCommand->str_param, game);
                break;
            case EDIT:
                game=edit(currCommand->str_param, game);
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
                save(currCommand->str_param, game);
                break;
            case HINT:
                hint(currCommand->int_params[0], currCommand->int_params[1], game);
                break;
            case GUESSHINT:
                break;
            case NUMSOLUTIONS:
                break;
            case AUTOFILL:
                autofill(game);
                break;
            case RESET:
                calc(game);
                break;
            case EXIT:
                exit_game(game);
                return 0;
                break;
            case INVALID:
            default:
                break;
        }
        print_board(game);
    }
    return 0;
}
