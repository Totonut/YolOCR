#include "HelloWorld.h"

int main(int argc, char *argv[])
{
	Initialisations();
	Boucle(argv[1]);
	Quitter();
	return EXIT_SUCCESS;
}

void Initialisations()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

int Boucle(char* image)
{
    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;
 
    positionFond.x = 0;
    positionFond.y = 0;
 
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
 
    imageDeFond = IMG_Load(image);
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
 
    SDL_Flip(ecran);
    Evenements();
 
    SDL_FreeSurface(imageDeFond);
    return 0;
}
 
void Evenements()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void Quitter()
{
	SDL_Quit();
}
 
 
