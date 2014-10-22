

SRC = neuralNetwork.c
OBJ = neuralNetwork.o
EXE = a.out

CC = clang 
CFLAGS = -Wall -Wextra -Werror -std=c99 -O3


all: main

main: $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) -o $(EXE) -lm
clean:
	@rm -f *~ *.o $(EXE)
