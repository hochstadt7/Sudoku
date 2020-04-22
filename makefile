CC = gcc
OBJS = main.o Game.o Autofill.o Parser.o Board.o FileManager.o ILP.o MainAux.o ValidBoard.o Generate.o Stack.o Solve.o
EXEC = sudoku-console
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@
main.o: main.c Game.h Parser.h ValidBoard.h Autofill.h ILP.h Solve.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Game.o: Game.c Board.h FileManager.h ValidBoard.h MainAux.h ILP.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Board.o: Board.c Board.h MainAux.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
MainAux.o: MainAux.c
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
FileManager.o: FileManager.c Board.h ValidBoard.h MainAux.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
ValidBoard.o: ValidBoard.c ValidBoard.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Generate.o: Generate.c Generate.h Board.h MainAux.h ILP.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Stack.o: Stack.c Stack.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
ILP.o: ILP.c ILP.h Board.h Autofill.h ValidBoard.h MainAux.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Solve.o: Solve.c Solve.h ValidBoard.h Stack.h MainAux.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
