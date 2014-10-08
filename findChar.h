#ifndef FIND_CHAR_H
#define FIND_CHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "perfectImage.h"
#ifdef __APPLE__
	#include <SDL_image/SDL_image.h>
	#include <SDL_ttf/SDL_ttf.h>
#else
	#include "SDL/SDL_image.h"
	#include "SDL_ttf.h"
#endif	

unsigned* findChar(SDL_Surface* ecran);
void drawLine(SDL_Surface* ecran, unsigned line);
unsigned *findLines(SDL_Surface* ecran);
unsigned* findChars(SDL_Surface* ecran, unsigned* lines);
void drawChar(SDL_Surface* ecran, unsigned x, unsigned y, unsigned w, unsigned h);

#endif
