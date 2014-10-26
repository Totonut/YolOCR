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

unsigned* findChar(SDL_Surface* ecran);
void drawLine(SDL_Surface* ecran, unsigned line);
unsigned findLines(SDL_Surface* ecran, unsigned *buffer);
unsigned* findChars(SDL_Surface* ecran, unsigned* lines, unsigned size);
void drawChar(SDL_Surface* ecran, unsigned x, unsigned y, unsigned w, unsigned h);
//int is_linked_pixel(unsigned* buffer1, unsigned* buffer2, size_t size, int i, int add);
//int is_linked(unsigned* buffer1, unsigned* buffer2, size_t size);
//void empty(unsigned* buffer, size_t lineHeight);
//void initialize(unsigned* buffer, size_t size);


#endif
