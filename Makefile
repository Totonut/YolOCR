CC=clang
CPPFLAGS= `pkg-config --libs --cflags gtk+-2.0`
CFLAGS=-Wall -Werror -Wextra -std=c99
LDLIBS=-lSDLmain -lSDL -lSDL_image
SRC = findChar.c perfectImage.c main.c 
OBJ = $(SRC:.c=.o)
EXE = YolOCR

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(SRC) -o $(EXE) -lm 

clean:
	rm -f *~ *.o
	rm -f YolOCR image.bmp image2.bmp
