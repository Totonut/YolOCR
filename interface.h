#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "findChar.h"
<<<<<<< HEAD
void afficher_findchar();
=======

struct newImage
{
	SDL_Surface* image;
	GdkPixbuf* pixbuf;
};
void afficher_findchar();//SDL_Surface *image);
>>>>>>> c05d5d0dcf1d84a8325077d90960c3afa6029a51
void open_window();

#endif
