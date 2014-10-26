#include "constantes.h"
#include "perfectImage.h"
#include "findChar.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    SDL_Surface *image = NULL;
    unsigned* chars = NULL;

    if (argc==2)
		image = IMG_Load(argv[1]);
    else
		image = IMG_Load("image.jpg");

 	open_window();
	
	
	
	
	
	SDL_Quit();
	return 0;
}
