#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Parser.h"

#define DELIMITER " \t\r\n"
#define COMMAND_COUNT 17
#define INVALID_COMMAND_ERROR "Error: invalid command\n"
#define TOO_LONG_ERROR "Error: command too long - commands should be shorter than %d characters\n"
#define TOO_MANY_PARAMS "Error: unexpected params - the %s command expects %d params\n"
#define INVALID_PARAM "Error: param format incorrect - please provide parameters of type %s\n"

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
void get_next_command(enum gameMode mode, struct Command* currMove){
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
    char* line;
    char* endptr = NULL; /* used to determine whether int/float params have been successfuly cast */
    command = NULL;
    currMove -> float_param = 0;
    currMove -> bool_param = 0;
    currMove -> int_params[0] = 0;
    currMove -> int_params[1] = 0;
    currMove -> int_params[2] = 0;
    currMove -> str_param = NULL;
    while(command==NULL){
        /*read command*/
        line=fgets(str, MAX_COMMAND_LENGTH, stdin);
        if( line == NULL || *line == '^'){
            currMove->type=EXIT;
            return;
        }
        /* notify user of command overflow */
        if(strlen(str) > MAX_COMMAND_LENGTH){
            printf(TOO_LONG_ERROR, MAX_COMMAND_LENGTH);
            currMove->type=INVALID;
            return;
        }
        /* extract command */
        command = strtok(str, DELIMITER);
        /*printf("test: string-%s", str);*/
    }
    /*look for command in commands list*/
    for(i = 0; i < COMMAND_COUNT; i++){
        if(strcmp(commands[i].name, command) == 0){
            /*once a command is identified, set the validCommand flag to TRUE, and get the required number of parameters for the command.*/
            expectedParamCount = commands[i].parCount;
            paramsOptional = commands[i].paramsOptional;
            paramType = commands[i].paramType;
            currMove->type = commands[i].type;
            isValidCommandType =
                    (mode == InitMode && commands[i].initMode) ||
                    (mode == EditMode && commands[i].editMode) ||
                    (mode == SolveMode && commands[i].solveMode);
            break;
        }
    }
    /*if the command is invalid - print an error*/
    if(!isValidCommandType){
        printf(INVALID_COMMAND_ERROR);
        currMove->type=INVALID;
        return;
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
            errno = 0;
            intParam = strtol(param, &endptr, 10);
            if(intParam == 0 && (errno != 0 || endptr == param)){
                printf(INVALID_PARAM, "int");
                currMove->type=INVALID;
                return;
            }
            currMove->int_params[i] = intParam;
        }
        if(paramType == PARAM_FLOAT){
            floatParam = strtof(param, NULL);
            currMove->float_param = floatParam;
        }
        if(paramType == PARAM_BOOL){
            boolParam = strtol(param, &endptr, 10);
            errno = 0;
            if((boolParam == 0 && (errno != 0 || endptr == param)) || boolParam < 0 || boolParam > 1){
                printf(INVALID_PARAM, "boolean");
                currMove->type=INVALID;
                return;
            }
            currMove->bool_param = boolParam;
        }
        if(paramType == PARAM_STR){
            if(param)
                currMove->str_param = param;
            else
                currMove->str_param = "";
        }
    }
    /*if some of the required params are missing - print an error message*/
    if(missingParams){
        printf(INVALID_COMMAND_ERROR);
        currMove->type=INVALID;
        return;
    }
    /*if unexpected parameters have been provided - print an error message*/
    param = strtok(NULL, DELIMITER);
    if(param != NULL){
        printf(TOO_MANY_PARAMS, command, expectedParamCount);
        currMove->type=INVALID;
        return;
    }
}

int get_move_type(struct Command* move){
    return move->type;
}
