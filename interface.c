#include <stdlib.h>
#include <gtk/gtk.h>
#include "interface.h"
void afficher_findchar(void);

void open_window()

{
    GtkWidget *pWindow,*pWindow2;
    GtkWidget *pVBox;
    GtkWidget *pImage;
	GdkPixbuf *pixbuf;
    GtkWidget *pQuitImage,*buttonFindChar;
    GtkWidget *pQuitBtn,*pEntry;
	GError *error=NULL;
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
       gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 	
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    /* Chargement d'une image a partir d'un fichier */
   // pImage = gtk_image_new_from_file("moto-kawasaki.jpg");
	pixbuf = gdk_pixbuf_new_from_file ("Image.jpg", &error); 
  if (!error) 
  { 
    GdkPixbuf *pixbuf_mini = NULL; 
  
    pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf, 
                                           900, 
                                           400, 
                                           GDK_INTERP_NEAREST); 
  
    pImage = gtk_image_new_from_pixbuf (pixbuf_mini);
  }
		
// TRUE/FALSE=> taille image/fenetre. 	
	
	
	
	
	
	  buttonFindChar = gtk_button_new_with_label("FindChar");
    gtk_box_pack_start(GTK_BOX(pVBox), buttonFindChar, FALSE,TRUE , 0);
	g_signal_connect(G_OBJECT(buttonFindChar), "clicked", G_CALLBACK(afficher_findchar), NULL);
 
	
	
	
	
	
	
	
	gtk_container_set_border_width (GTK_CONTAINER (pWindow), 100);

	gtk_window_set_default_size(GTK_WINDOW(pWindow), 200, 200);
	 //gtk_widget_set_size_request(pImage, 200, 200);
	 gtk_window_move(GTK_WINDOW(pWindow),  0,  600);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, TRUE, 0);

	    gtk_widget_show_all(pWindow);
 
    gtk_main();
 
    return EXIT_SUCCESS;
}

void afficher_findchar(void)
{

	GtkWidget *pWindow, *pEntry, *pVBox,*view;
	pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_move(GTK_WINDOW(pWindow),  1000,  300);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), 		NULL);
//	pEntry = gtk_entry_new();
   view = gtk_text_view_new(); 
	
	pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
	gtk_box_pack_start(GTK_BOX(pVBox), view, TRUE, TRUE, 0);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 200, 200);
//	gtk_entry_set_text(GTK_ENTRY(pEntry), "Saisissez votre texte! :D ");

	 gtk_widget_show_all(pWindow);
 


		

}

void on_copier_button(GtkWidget *pButton, gpointer data)
{
    GtkWidget *pTempEntry;
    GtkWidget *pTempLabel;
    GList *pList;
    const gchar *sText;
 
    /* Recuperation de la liste des elements que contient la GtkVBox */
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
 
    /* Le premier element est le GtkEntry */
    pTempEntry = GTK_WIDGET(pList->data);
 
    /* Passage a l element suivant : le GtkButton */
    pList = g_list_next(pList);
 
    /* Passage a l element suivant : le GtkLabel */
    pList = g_list_next(pList);
 
    /* Cet element est le GtkLabel */
    pTempLabel = GTK_WIDGET(pList->data);
 
    /* Recuperation du texte contenu dans le GtkEntry */
    sText = gtk_entry_get_text(GTK_ENTRY(pTempEntry));
 
    /* Modification du texte contenu dans le GtkLabel */
    gtk_label_set_text(GTK_LABEL(pTempLabel), sText);
 
    /* Liberation de la memoire utilisee par la liste */
    g_list_free(pList);
}
