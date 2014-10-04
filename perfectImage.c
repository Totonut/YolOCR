#include "perfectImage.h"

void perfectImage(SDL_Surface* ecran)
{
    Uint32 pixel = 0;
    Uint8 r = 0, g = 0, b = 0;
    for (int i=0; i<ecran->w;i++)
    {
	for (int j=0; j<ecran->h;j++)
	{
	    pixel = obtenirPixel(ecran, i, j);

	    r = (pixel & 0x000000ff);
	    g = (pixel & 0x0000ff00) >> 8;
	    b = (pixel & 0x00ff0000) >> 16;
	    if (r + g + b > 384)
	    {
	    	pixel =  0x00ffffff;
	    } 
	    else
	    {
	    	pixel =  0x00000000;
	    } 
	    definirPixel(ecran, i, j, pixel);
	}
    }

}

Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    switch(nbOctetsParPixel)
    {
	case 1:
	    return *p;
	case 2:
	    return *(Uint16 *)p;
	case 3:
	    /*Suivant l'architecture de la machine*/
	    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		return p[0] << 16 | p[1] << 8 | p[2];
	    else
		return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
	    return *(Uint32 *)p;
	    /*Ne devrait pas arriver, mais évite les erreurs*/
	default:
	    return 0; 
    }
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
	case 1:
	    *p = pixel;
	    break;
	case 2:
	    *(Uint16 *)p = pixel;
	    break;
	case 3:
	    /*Suivant l'architecture de la machine*/
	    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	    {
		p[0] = (pixel >> 16) & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = pixel & 0xff;
	    }
	    else
	    {
		p[0] = pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (pixel >> 16) & 0xff;
	    }
	    break;
	case 4:
	    *(Uint32 *)p = pixel;
	    break;
    }
}
