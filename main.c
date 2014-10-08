#include "constantes.h"
#include "perfectImage.h"
#include "findChar.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *image = NULL, *imageButton1=NULL, *imageButton2=NULL, *button1_1=NULL, *button1_2=NULL, *button2_1=NULL, *button2_2;
    SDL_Rect positionImage, positionButton1, positionButton2;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_WM_SetIcon(IMG_Load("icone.jpg"), NULL);
    ecran = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("YolOCR", NULL);
    if (argv[1]!=NULL)
	image = IMG_Load(argv[1]);
    else
	image = IMG_Load("image.jpg");
    button1_1=IMG_Load("images/button1_1.jpg");
    button1_2=IMG_Load("images/button1_2.jpg");
    button2_1=IMG_Load("images/button2_1.jpg");
    button2_2=IMG_Load("images/button2_2.jpg");
    imageButton1=button1_1;
    imageButton2=button2_1;

    positionImage.x = 0;
    positionImage.y = 70;
    positionButton1.x = 10;
    positionButton1.y = 5;
    positionButton2.x = 170;
    positionButton2.y = 5;

    while (continuer)
    {
	SDL_WaitEvent(&event);
	switch(event.type)
	{
	    case SDL_QUIT:
		continuer = 0;
		break;
	    case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
		{
		    case SDLK_ESCAPE:
			continuer = 0;
			break;
		    case SDLK_KP1:
			perfectImage(image);
			break;
		    case SDLK_KP2:
			findChar(image);
			break;
		    default:
			break;
		}
		break;
	    case SDL_MOUSEMOTION:
		if (event.button.x >= positionButton1.x && event.button.x <= positionButton1.x + BUTTON_WIDTH && event.button.y >= positionButton1.y && event.button.y < positionButton1.y + BUTTON_HEIGHT)
		    imageButton1 = button1_2;
		else
		    imageButton1 = button1_1;
		if (event.button.x >= positionButton2.x && event.button.x <= positionButton2.x + BUTTON_WIDTH && event.button.y >= positionButton2.y && event.button.y < positionButton2.y + BUTTON_HEIGHT)  
		    imageButton2 = button2_2;
		else
		    imageButton2 = button2_1;	
		break;
	    case SDL_MOUSEBUTTONUP:
		if (event.button.x >= positionButton1.x && event.button.x <= positionButton1.x + BUTTON_WIDTH && event.button.y >= positionButton1.y && event.button.y < positionButton1.y + BUTTON_HEIGHT)
		{
		    perfectImage(image);
		}
		if (event.button.x >= positionButton2.x && event.button.x <= positionButton2.x + BUTTON_WIDTH && event.button.y >= positionButton2.y && event.button.y < positionButton2.y + BUTTON_HEIGHT)  
		{
		    findChar(image);
		}
		break;
	    default:
		break;
	}

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_BlitSurface(image, NULL, ecran, &positionImage);
	SDL_BlitSurface(imageButton1, NULL, ecran, &positionButton1);
	SDL_BlitSurface(imageButton2, NULL, ecran, &positionButton2);

	SDL_Flip(ecran);
    }

    SDL_FreeSurface(image);
    SDL_FreeSurface(button1_1);
    SDL_FreeSurface(button1_2);
    SDL_FreeSurface(button2_1);
    SDL_FreeSurface(button2_2);

    TTF_Init(); 
    SDL_Quit();
    return EXIT_SUCCESS;
}
