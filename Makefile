CC=clang
CFLAGS=-Wall -Wextra -std=c99 -O2 -lSDLmain -lSDL -lSDL_image -lSDL_ttf findChar.c perfectImage.c  

all:
	@echo "*** NO RULES ***"
	@false

clean:
	rm -f *~ *.o
	rm -f main
