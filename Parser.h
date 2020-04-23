#ifndef BIGPROJECT_PARSER_H
#define BIGPROJECT_PARSER_H
#include "Board.h"
#define MAX_COMMAND_LENGTH 256
/*the parser module intercepts user input, and parses it into a command object, which can later be analyzed by the game loop*/
enum commandTypes {
    SOLVE=1, EDIT=2, MARK_ERRORS=3, PRINT_BOARD=4,
    SET=5, VALIDATE=6, GUESS=7, GENERATE=8,
    UNDO=9, REDO=10, SAVE=11,
    HINT=12, GUESSHINT=13, NUMSOLUTIONS=14, AUTOFILL=15,
    RESET=16, EXIT=17,
    INVALID=0
}; /* each command has an associated enum value, for ease of reference*/
enum paramTypes {PARAM_INT, PARAM_BOOL, PARAM_FLOAT, PARAM_STR}; /*possible data types for parameters*/
typedef struct CommandSyntax{
    char* name;
    int parCount;
    int paramsOptional;
    enum paramTypes paramType;
    int initMode; /*is the command available in init mode*/
    int editMode; /*is the command available in edit mode*/
    int solveMode; /*is the command available in solve mode*/
    enum commandTypes type;
}CommandSyntax; /*each command syntax struct contains a possible way to interpret a command string*/
typedef struct Command{
    enum commandTypes type;
    int int_params[3];
    char* str_param;
    float float_param;
    int bool_param;
}Command; /*the command object is used to communicate the essential details about the input command to the game*/
void get_next_command(enum gameMode mode, struct Command* move);/*waits for user input, and returns set the properties
 * of the provided command struct once a valid command is identified*/
int get_move_type(struct Command* move);/*returns the enum of the command type associated with a provided command struct*/
#endif /*BIGPROJECT_PARSER_H*/
