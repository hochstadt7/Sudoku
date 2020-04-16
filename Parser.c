#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Parser.h"

#define DELIMITER " \t\r\n"
#define COMMAND_COUNT 17
#define MAX_COMMAND_LENGTH 256
#define INVALID_COMMAND_ERROR "Error: invalid command\n"
#define TOO_LONG_ERROR "Error: command too long - commands should be shorter than %d characters\n"
#define TOO_MANY_PARAMS "Error: unexpected params - the %s command expects %d params\n"
#define INVALID_PARAM "Error: param format incorrect - please provide parameters of type %s\n"

struct Command invalidMove = {
        INVALID, {0}
};
/*an object containing an enum indicating the selected command type*/
/*and an array of all parameters relevant to the current command*/
struct Command currMove = {
        INVALID, {0}, "", 0.0f, 0
};
struct CommandSyntax commands[COMMAND_COUNT] = {
        {"solve", 1, 0, PARAM_STR,1, 1, 1, SOLVE},
        {"edit", 1, 1, PARAM_STR, 1, 1, 1, EDIT},
        {"mark_errors", 1, 0, PARAM_BOOL, 0, 0, 1, MARK_ERRORS},
        {"print_board", 0, 0, PARAM_INT, 0, 1, 1, PRINT_BOARD},
        {"set", 3, 0, PARAM_INT, 0, 1, 1, SET},
        {"validate", 0, 0, PARAM_INT, 0, 1, 1, VALIDATE},
        {"guess", 1, 0, PARAM_FLOAT, 0, 0, 1, GUESS},
        {"generate", 2, 0, PARAM_INT, 0, 1, 0, GENERATE},
        {"undo", 0, 0, PARAM_INT, 0, 1, 1, UNDO},
        {"redo", 0, 0, PARAM_INT, 0, 1, 1, REDO},
        {"save", 1, 0, PARAM_STR, 0, 1, 1, SAVE},
        {"hint", 2, 0, PARAM_INT, 0, 0, 1, HINT},
        {"guesshint", 2, 0, PARAM_INT, 0, 0, 1, GUESSHINT},
        {"numsolutions", 0, 0, PARAM_INT, 0, 1, 1, NUMSOLUTIONS},
        {"autofill", 0, 0, PARAM_INT, 0, 0, 1, AUTOFILL},
        {"reset", 0, 0, PARAM_INT, 0, 1, 1, RESET},
        {"exit", 0, 0, PARAM_INT, 1, 1, 1, EXIT}
};
struct Command* get_next_command(enum gameModes mode){
    char str [MAX_COMMAND_LENGTH]; /* the input string*/
    char* command; /* the substring representing the command type*/
    char* param; /* the substring of the command representing the currently processed parameter;*/
    enum paramTypes paramType = 0; /* the type of the params associated with the identified command */
    int intParam; /* the currently processed param after a str to int casting*/
    float floatParam; /* the currently processed param after a str to float casting*/
    int boolParam; /* the currently processed param after a str to bool casting*/
    int isValidCommandType = 0; /* whether the input command type is valid*/
    int expectedParamCount = 0; /* the number of parameters we expect for the selected command*/
    int paramsOptional = 0;
    int missingParams = 0; /* whether or not a sufficient*/
    int i = 0;
    char* test;
    char* endptr = NULL; /* used to determine whether int/float params have been successfully cast */
    command = NULL;
    while(command==NULL){
        /*read command*/
        test=fgets(str, MAX_COMMAND_LENGTH, stdin);
        if( test == NULL || *test == '^'){
            currMove.type=EXIT;
            return &currMove;
        }
        /* notify user of command overflow */
        if(strlen(str) > MAX_COMMAND_LENGTH){
            printf(TOO_LONG_ERROR, MAX_COMMAND_LENGTH);
            return &invalidMove;
        }
        /* extract command */
        command = strtok(str, DELIMITER);
        printf("test: string-%s", str);
    }
    /*look for command in commands list*/
    for(i = 0; i < COMMAND_COUNT; i++){
        if(strcmp(commands[i].name, command) == 0){
            /*once a command is identified, set the validCommand flag to TRUE, and get the required number of parameters for the command.*/
            expectedParamCount = commands[i].parCount;
            paramsOptional = commands[i].paramsOptional;
            paramType = commands[i].paramType;
            currMove.type = commands[i].type;
            isValidCommandType =
                    (mode == MODEINIT && commands[i].initMode) ||
                    (mode == MODEEDIT && commands[i].editMode) ||
                    (mode == MODESOLVE && commands[i].solveMode);
            break;
        }
    }
    /*if the command is invalid - print an error*/
    if(!isValidCommandType){
        printf(INVALID_COMMAND_ERROR);
        return &invalidMove;
    }
    /*iterate through the supplied params (space delimited), parse them as integers, and add them to the command parameters array.*/
    for(i = 0; i < expectedParamCount; i++){
        param = strtok(NULL, DELIMITER);
        /*if there are no addition space delimited values*/
        if(param == NULL && !paramsOptional){
            missingParams = 1;
            break;
        }
        if(paramType == PARAM_INT){
            intParam = strtol(param, &endptr, 10);
            if(intParam == 0 && (errno != 0 || endptr == param)){
                printf(INVALID_PARAM, "int");
                return &invalidMove;
            }
            currMove.int_params[i] = intParam;
        }
        if(paramType == PARAM_FLOAT){
            floatParam = strtof(param, NULL);
            currMove.float_param = floatParam;
        }
        if(paramType == PARAM_BOOL){
            boolParam = strtol(param, &endptr, 10);
            if((boolParam == 0 && (errno != 0 || endptr == param)) || boolParam < 0 || boolParam > 1){
                printf(INVALID_PARAM, "boolean");
                return &invalidMove;
            }
            currMove.bool_param = boolParam;
        }
        if(paramType == PARAM_STR){
            currMove.str_param = param;
        }
    }
    /*if some of the required params are missing - print an error message*/
    if(missingParams){
        printf(INVALID_COMMAND_ERROR);
        return &invalidMove;
    }
    /*if unexpected parameters have been provided - print an error message*/
    param = strtok(NULL, DELIMITER);
    if(param != NULL){
        printf(TOO_MANY_PARAMS, command, expectedParamCount);
        return &invalidMove;
    }
    return &currMove;
}

int* get_move_int_params(struct Command* move){
    return move->int_params;
}

float get_move_float_params(struct Command* move){
    return move->float_param;
}

int get_move_bool_params(struct Command* move){
    return move->bool_param;
}

char* get_move_str_params(struct Command* move){
    return move->str_param;
}

int get_move_type(struct Command* move){
    return move->type;
}