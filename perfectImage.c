#include "perfectImage.h"

void perfectImage(SDL_Surface* screen)
{
    Uint32 pixel = 0;
    Uint8 r = 0, g = 0, b = 0;
    for (int i=0; i<screen->w;i++)
    {
	for (int j=0; j<screen->h;j++)
	{
	    pixel = getPix(screen, i, j);

	    r = (pixel & 0x000000ff);
	    g = (pixel & 0x0000ff00) >> 8;
	    b = (pixel & 0x00ff0000) >> 16;
	    if (0.3*r + 0.58*g + 0.11*b > 128)
	    {
		pixel =  0x00ffffff;
	    } 
	    else
	    {
		pixel =  0x00000000;
	    } 
	    setPix(screen, i, j, pixel);
	}
    }

}

Uint32 getPix(SDL_Surface *surface, int x, int y)
{
    int nbOctPerPix = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels 
	+ y * surface->pitch + x * nbOctPerPix;

    switch(nbOctPerPix)
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

void setPix(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int nbOctPerPix = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels 
	+ y * surface->pitch + x * nbOctPerPix;
    switch(nbOctPerPix)
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

int isValid(int x, int y, int width, int height)
{
    return (x < 0 || x > width || y < 0 || y > height) ? 0 : 1;
}

void Convolution(SDL_Surface* screen, float mat[3][3])
{
    int width = screen -> w, height = screen -> h;
    float r = 0;
    for (int y = 0; y < height; ++y)
    {
	for (int x = 0; x < width; ++x)
	{
	    r = 0.;
	    for (int dy = -1; dy <= 1; ++dy)
	    {
		for (int dx = -1; dx <= 1; ++dx)
		{
		    if (isValid(x + dx, y + dy, width, height))
		    {
			Uint32 pixel = getPix(screen, x + dx, y + dy);
			r += (pixel & 0x000000ff) * (mat[dy+1][dx+1]/9.);
		    }
		}
	    }
	    if (r > 128)
		setPix(screen, x, y, 0x00ffffff);
	    else
		setPix(screen, x, y, 0x00000000);
	}
    }	
}

void gommage (SDL_Surface *screen)
{
    float matgommage[][3] = {{1,1,1},{1,5,1},{1,1,1}};
    Convolution(screen , matgommage);
}

void contraste (SDL_Surface *screen)
{
    float matcontraste[][3] = {{0,-1,0},{-1,5,-1},{0,-1,0}};
    Convolution(screen , matcontraste);
}

void sound_reduction (SDL_Surface *screen)
{
//	gommage(screen);
//	contraste(screen);
}


