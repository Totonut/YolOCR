CC=clang
CFLAGS=-Wall -Wextra -std=c99 -O2 `sdl-config --libs` -I /Library/Frameworks/SDL.framework/Headers -framework SDL_image -framework SDL_ttf findChar.c perfectImage.c SDLmain.m 
SDL_1:SDL_1.c SDLmain.o
SDLmain.o:SDLmain.h SDLmain.m

all:
	@echo "*** NO RULES ***"
	@false

clean:
	rm -f *~ *.o
 
