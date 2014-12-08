CC=clang

CFLAGS=-Wall -Wextra -std=c99 -Werror `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image  findChar.c perfectImage.c  
CFLAGS=-Wall -Wextra -std=c99 -O2 `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image -lSDL_ttf findChar.c perfectImage.c interface.c tabPix.c 
CFLAGS=-Wall -Wextra -std=c99  `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image findChar.c perfectImage.c tabPix.c

all:
	@NO-RULES
	@false

clean:
	rm -f *~ *.o
	rm -f main
	rm -f image.bmp image2.bmp
