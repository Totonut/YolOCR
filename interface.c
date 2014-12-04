#include <stdlib.h>
#include <gtk/gtk.h>
#include "interface.h"

void open_window()
{
    GtkWidget *pWindow, *pVBox, *pHBox, *pImage, *pImage2;
	GdkPixbuf *pixbuf, *pixbuf2;
	GtkWidget *buttonFindChar;
    
	GError *error=NULL;
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit),
			NULL);

		
 	pHBox= gtk_hbox_new(FALSE,8);
    pVBox = gtk_vbox_new(FALSE, 8);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 	gtk_container_add(GTK_CONTAINER(pWindow),pHBox);
	pixbuf2=gdk_pixbuf_new_from_file("image2.bmp", &error);
	pixbuf = gdk_pixbuf_new_from_file ("image.bmp", &error); 
    GdkPixbuf *pixbuf_mini = NULL; 
	GdkPixbuf *pixbuf_mini2=NULL;
	pixbuf_mini2=gdk_pixbuf_scale_simple(pixbuf2,650,450,
	GDK_INTERP_NEAREST);
    pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf,650, 450, 
            GDK_INTERP_NEAREST); 
    pImage2=gtk_image_new_from_pixbuf(pixbuf_mini2);
    pImage = gtk_image_new_from_pixbuf (pixbuf_mini);
    buttonFindChar = gtk_button_new_with_label("FindChar");
    gtk_box_pack_start(GTK_BOX(pVBox), buttonFindChar, FALSE,TRUE , 0);
    g_signal_connect(G_OBJECT(buttonFindChar), "clicked",
			  G_CALLBACK(afficher_findchar), NULL);
 	gtk_container_set_border_width (GTK_CONTAINER (pWindow), 30);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 200, 200);
    gtk_window_move(GTK_WINDOW(pWindow),  0,  600);
	gtk_box_pack_start(GTK_BOX(pHBox), pImage, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pHBox),pImage2,FALSE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(pVBox),pHBox,FALSE,TRUE,0);
	    gtk_widget_show_all(pWindow);
    gtk_main();
 
}

void afficher_findchar()
{
	GtkWidget *pWindow, *pVBox,*view;
	pWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_move(GTK_WINDOW(pWindow),  50,  80);
	g_signal_connect(G_OBJECT(pWindow), "delete-event",
			G_CALLBACK(gtk_widget_hide_on_delete),G_OBJECT(pWindow));
    view = gtk_text_view_new(); 
	pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
	gtk_box_pack_start(GTK_BOX(pVBox), view, TRUE, TRUE, 0);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 700, 450);
    gtk_widget_show_all(pWindow);
 


		

}
void on_copier_button(gpointer data)
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
