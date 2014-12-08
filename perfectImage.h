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
int isValid(int x, int y, int width, int height);
void Convolution(SDL_Surface* screen, float mat[3][3]);
void gommage (SDL_Surface *screen);
void contraste (SDL_Surface *screen);
void sound_reduction (SDL_Surface *screen);
#endif
