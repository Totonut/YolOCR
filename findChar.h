#ifndef FIND_CHAR_H
#define FIND_CHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "tabPix.h"
#include "perfectImage.h"
#include <string.h>
#include "neuralNetwork.h"
#ifdef __APPLE__
	#include <SDL_image/SDL_image.h>
#else
	#include "SDL/SDL_image.h"
#endif	

int *find_chars(SDL_Surface* screen, unsigned *lines, unsigned size, unsigned *nb_chars);
char *find_char(SDL_Surface* screen);
unsigned *find_lines(SDL_Surface* screen, unsigned *nb_lines);
void draw_char(SDL_Surface* screen, unsigned x, unsigned y,
	unsigned w, unsigned h, Uint32 color);


#endif
