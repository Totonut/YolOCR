#ifndef TAB_PIX_H
#define TAB_PIX_H

#include "perfectImage.h"
#include "findChar.h"
#include <strings.h>


unsigned int **transformPix(unsigned int *tabPix, SDL_Surface *screen);
int *transformPix2(unsigned x, unsigned y, unsigned w, unsigned h, SDL_Surface *screen);
   


#endif
