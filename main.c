#include "constantes.h"
#include "perfectImage.h"
#include "interface.h"
#include "findChar.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


int main(int argc, char *argv[])
{	
    gtk_init(&argc, &argv);
    SDL_Surface *image = NULL;

    if (argc==2)
		image = IMG_Load(argv[1]);
    else
		image = IMG_Load("image.jpg");
	SDL_SaveBMP(image, "image.bmp");
	perfectImage(image);
 	find_char(image);
	SDL_SaveBMP(image, "image2.bmp");
    	create_window();
		SDL_FreeSurface(image);	
	
	SDL_Quit();
	return 0;
}
