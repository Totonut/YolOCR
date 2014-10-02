CC=clang
CFLAGS=-Wall -Wextra -std=c99 -O2 -lSDLmain -lSDL -lSDL_image

all:
	@echo "*** NO RULES ***"
	@false

clean:
	rm -f *~ *.o
 
