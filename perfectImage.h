#ifndef PERFECT_IMAGE_H
#define PERFECT_IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL_ttf.h>

void perfectImage(SDL_Surface* ecran);
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);
void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif
