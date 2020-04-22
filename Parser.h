#ifndef BIGPROJECT_PARSER_H
#define BIGPROJECT_PARSER_H
#include "Board.h"
enum commandTypes {
    SOLVE=1, EDIT=2, MARK_ERRORS=3, PRINT_BOARD=4,
    SET=5, VALIDATE=6, GUESS=7, GENERATE=8,
    UNDO=9, REDO=10, SAVE=11,
    HINT=12, GUESSHINT=13, NUMSOLUTIONS=14, AUTOFILL=15,
    RESET=16, EXIT=17,
    INVALID=0
};
enum paramTypes {PARAM_INT, PARAM_BOOL, PARAM_FLOAT, PARAM_STR};
typedef struct CommandSyntax{
    char* name;
    int parCount;
    int paramsOptional;
    enum paramTypes paramType;
    int initMode; /*is the command available in init mode*/
    int editMode; /*is the command available in edit mode*/
    int solveMode; /*is the command available in solve mode*/
    enum commandTypes type;

}CommandSyntax;
typedef struct Command{
    enum commandTypes type;
    int int_params[3];
    char* str_param;
    float float_param;
    int bool_param;
}Command;
Command* get_next_command(enum gameMode mode);
int* get_move_int_params(struct Command* move);
float get_move_float_params(struct Command* move);
int get_move_bool_params(struct Command* move);
char* get_move_str_params(struct Command* move);
int get_move_type(struct Command* move);
#endif /*BIGPROJECT_PARSER_H*/
