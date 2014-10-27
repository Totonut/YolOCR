#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "findChar.h"

struct newImage
{
	SDL_Surface* image;
	GdkPixbuf* pixbuf;
};
void afficher_findchar();//SDL_Surface *image);
void open_window(int argc, char* argv[], SDL_Surface* image);

#endif
