cmake_minimum_required(VERSION 3.15)
project(Bigproject C)

set(CMAKE_C_STANDARD 90)

add_executable(Bigproject main.c Game.c Game.h Board.h Board.c MainAux.c MainAux.h Interface.c Interface.h Edit.c Edit.h Init.c Init.h Solve.c Solve.h History.c History.h ILP.c ILP.h Parser.c Parser.h Stack.c Stack.h FileManager.c FileManager.h)