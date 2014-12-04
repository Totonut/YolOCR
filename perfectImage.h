#ifndef PERFECT_IMAGE_H
#define PERFECT_IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
	#include <SDL_image/SDL_image.h>
#else
	#include "SDL/SDL_image.h"
#endif		

void perfectImage(SDL_Surface* screen);
Uint32 getPix(SDL_Surface *surface, int x, int y);
void setPix(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif
