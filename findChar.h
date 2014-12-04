#ifndef FIND_CHAR_H
#define FIND_CHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "perfectImage.h"
#include <string.h>
#ifdef __APPLE__
	#include <SDL_image/SDL_image.h>
#else
	#include "SDL/SDL_image.h"
#endif	

unsigned* find_char(SDL_Surface* screen);
unsigned find_lines(SDL_Surface* screen, unsigned *buffer);
void draw_char(SDL_Surface* screen, unsigned x, unsigned y,
	unsigned w, unsigned h, Uint32 color);


#endif
