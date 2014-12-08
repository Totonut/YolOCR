#ifndef FIND_CHAR_H
#define FIND_CHAR_H

#include "constantes.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <SDL/SDL.h>
#include "tabPix.h"
#include "perfectImage.h"
#include <string.h>
#include "neuralNetwork.h"
//#include "SDL/SDL_image.h"

int *find_chars(SDL_Surface* screen, unsigned *lines, unsigned size, unsigned *nb_chars);
char *find_char(SDL_Surface* screen, struct neuron **net, int *layers_Size, int layers, char *chars);
unsigned *find_lines(SDL_Surface* screen, unsigned *nb_lines);
void draw_char(SDL_Surface* screen, unsigned x, unsigned y,
	unsigned w, unsigned h, Uint32 color);


#endif
