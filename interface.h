#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "findChar.h"

void afficher_findchar();

struct newImage
{
	SDL_Surface* image;
	GdkPixbuf* pixbuf;
};
void on_copier_button(gpointer data);
void open_window();

#endif
