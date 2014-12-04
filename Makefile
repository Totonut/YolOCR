CC=clang
<<<<<<< HEAD
CFLAGS=-Wall -Wextra -std=c99 -O2 `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image -lSDL_ttf findChar.c perfectImage.c interface.c 
=======
CFLAGS=-Wall -Wextra -std=c99 -Werror `pkg-config --libs --cflags gtk+-2.0` -lSDLmain -lSDL -lSDL_image findChar.c perfectImage.c
>>>>>>> c05d5d0dcf1d84a8325077d90960c3afa6029a51

all:
	@NO-RULES
	@false

clean:
	rm -f *~ *.o
	rm -f main
	rm -f image.bmp image2.bmp
