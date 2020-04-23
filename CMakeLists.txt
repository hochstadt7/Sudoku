cmake_minimum_required(VERSION 3.15)
project(Bigproject C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0 -ansi -Wall -Wextra -Werror -pedantic-errors")
add_executable(Bigproject main.c Game.c Game.h Board.h Board.c MainAux.c MainAux.h Parser.c Parser.h Stack.c Stack.h FileManager.c FileManager.h ValidBoard.c ValidBoard.h Generate.c Generate.h Autofill.c Autofill.h ILP.c ILP.h Solve.c Solve.h)