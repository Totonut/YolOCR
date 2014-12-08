#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "findChar.h"
#include "perfectImage.h"

void afficher_findchar();

struct newImage
{
	SDL_Surface* image;
	GdkPixbuf* pixbuf;
};
void on_copier_button(gpointer data);
void create_window();
static void menu_new (void);
static gchar * menu_open (void);
static void menu_quit (void);
static void menu_help (void);
static void menu_about (void);
//static void menu_addWidget (GtkUIManager *,GtkWidget *, GtkContainer *);
static void menu_addWidget (GtkUIManager *  p_uimanager, GtkWidget *, GtkContainer *);
void main2();
void factorize(GtkWidget *p_vBox);
void open_image(gchar *sChemin ,GtkWidget *p_vBox);
static void Binarize (void);

#endif
