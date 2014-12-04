

SRC = neuralNetwork.c perfectImage.c
OBJ = neuralNetwork.o perfectImage.o
EXE = a.out

CC = clang 
CFLAGS = -Wall -Wextra -std=c99 -lSDLmain -lSDL -lSDL_image -lSDL_ttf


all: main

main: $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) -o $(EXE) -lm
clean:
	@rm -f *~ *.o $(EXE)
