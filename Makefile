CC=clang
CFLAGS=-Wall -Wextra -std=c99 -Werror `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image findChar.c perfectImage.c

all:
	@NO-RULES
	@false

clean:
	rm -f *~ *.o
	rm -f main
