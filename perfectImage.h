#ifndef PERFECT_IMAGE_H
#define PERFECT_IMAGE_H

#include "constantes.h"
#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <SDL/SDL.h>
//#include "SDL/SDL_image.h"	

void perfectImage(SDL_Surface* screen);
Uint32 getPix(SDL_Surface *surface, int x, int y);
void setPix(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif
