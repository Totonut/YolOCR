CC=clang
CFLAGS=-Wall -Wextra -std=c99 -O2 -lSDLmain -lSDL -lSDL_image -lSDL_ttf

all:
	@echo "*** NO RULES ***"
	@false

clean:
	rm -f *~ *.o
 
