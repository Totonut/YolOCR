#include "constantes.h"
#include "perfectImage.h"
#include "findChar.h"
#include "interface.h"
#include "interface.c"

int main(int argc, char *argv[])
{
	
    gtk_init(&argc, &argv);
    SDL_Surface *image = NULL;
    unsigned* chars = NULL;

    if (argc==2)
		image = IMG_Load(argv[1]);
    else
		image = IMG_Load("image.jpg");
	SDL_SaveBMP(image, "image.bmp");
	printf("BP1 !!!%s\n", image);
	perfectImage(image);
	printf("BP2 !!!\n");
	findChar(image);
	printf("BP3 !!!\n");
	SDL_SaveBMP(image, "image2.bmp");
	open_window(&argc, &argv, image);
	
	SDL_FreeSurface(image);	
	
	SDL_Quit();
	return 0;
}
