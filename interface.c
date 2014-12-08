#include <stdlib.h>
//#include <gtk/gtk.h>
#include "interface.h"

GtkWidget *pWindow;
GtkWidget *p_vBox;
GtkWidget *p_hBox;
// $  gcc $(pkg-config --libs --cflags gtk+-2.0) main.c -o nom    

void create_window() //gchar *sChemin)
{
    p_hBox=gtk_hbox_new(FALSE,0);

    GtkWidget *buttonFindChar;
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_screen(display, 0);
    int 	screen_width = gdk_screen_get_width(screen);
    int 	screen_height = gdk_screen_get_height(screen);
    GError *error=NULL;

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit),
	    NULL);
    p_vBox = gtk_vbox_new (FALSE, 0);

    GtkUIManager *p_uiManager = NULL;
    GtkActionGroup *p_actionGroup = NULL;
    GtkActionEntry entries[] = {
	{"FichierMenuAction", NULL, "Fichier", NULL, NULL, NULL},
	{"NouveauAction", GTK_STOCK_SAVE_AS, "Enregistrer", "<Control>N", "Enregistrer", G_CALLBACK (menu_new)},
	{"OuvrirAction", GTK_STOCK_OPEN, "Ouvrir", "<Control>O", "Ouvrir",
	    G_CALLBACK(menu_open)}, 
	{"QuitterAction", GTK_STOCK_QUIT, "Quitter", "<control>Q", "Quitter",
	    G_CALLBACK (menu_quit)},
	{"AideMenuAction", NULL, "Aide", NULL, NULL, NULL},
	{"AideAction", GTK_STOCK_HELP, "Aide", "<Release>F1", "Aide",
	    G_CALLBACK (menu_help)},
	{"AproposAction", GTK_STOCK_ABOUT, "A propos", "<Control>A", "About",
	    G_CALLBACK (menu_about)},
	{"Rotation", GTK_STOCK_ABOUT, "Rotation", "<Control>A", "Rotation",
	    G_CALLBACK (menu_about)},
	{"Binarize",GTK_STOCK_INDENT, "Binarize","<Control>B","Binarize",G_CALLBACK(Binarize)}
    };


    //	pHBox= gtk_vbox_new(FALSE,8);
    // pVBox = gtk_vbox_new(FALSE, 8);
    //gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
    //gtk_container_add(GTK_CONTAINER(pWindow),pHBox );
    /*	pixbuf2=gdk_pixbuf_new_from_file("image2.bmp", &error);
	pixbuf = gdk_pixbuf_new_from_file (sChemin, &error); 
	GdkPixbuf *pixbuf_mini = NULL; 
	GdkPixbuf *pixbuf_mini2=NULL;
    //pixbuf_mini2=gdk_pixbuf_scale_simple(pixbuf2,625,450,
    //	GDK_INTERP_NEAREST);
    pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf,625, 450, 
    GDK_INTERP_NEAREST); 
    pImage2=gtk_image_new_from_pixbuf(pixbuf_mini2);
    pImage = gtk_image_new_from_pixbuf (pixbuf_mini);
    buttonFindChar = gtk_button_new_with_label("FindChar");
    g_signal_connect(G_OBJECT(buttonFindChar), "clicked",
    G_CALLBACK(afficher_findchar), NULL);*/

    gtk_container_set_border_width (GTK_CONTAINER (pWindow), 10);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), screen_width, screen_height);
    gtk_window_move(GTK_WINDOW(pWindow),  0,  600);

    /* Creation du menu */
    p_uiManager = gtk_ui_manager_new ();
    p_actionGroup = gtk_action_group_new ("menuActionGroup");
    gtk_action_group_add_actions (p_actionGroup, entries,
	    G_N_ELEMENTS (entries), NULL);
    gtk_ui_manager_insert_action_group (p_uiManager, p_actionGroup, 0);
    gtk_ui_manager_add_ui_from_file (p_uiManager, "menu.xml", NULL);

    //gtk_box_pack_start(GTK_BOX(pVBox),pHBox,FALSE,TRUE,0);


    //	  gtk_container_add (GTK_CONTAINER (pHBox), p_vBox);

    // gtk_box_pack_end(GTK_BOX(p_vBox), buttonFindChar, FALSE,TRUE , 0);
    //	gtk_box_pack_end(GTK_BOX(p_vBox), pImage, TRUE, TRUE, 0);

    //gtk_box_pack_end(GTK_BOX(p_vBox),pImage2,FALSE,TRUE,0);	
    gtk_container_add(GTK_CONTAINER(pWindow),p_vBox );

    g_signal_connect
	(p_uiManager, "add_widget", G_CALLBACK (menu_addWidget), p_vBox); 
    gtk_widget_show_all(pWindow);

    gtk_main();


}


void open_image (gchar * sChemin, GtkWidget *p_vBox)
{		 GtkWidget *pImage;
    GdkPixbuf *pixbuf;
    GtkWidget *buttonFindChar;

    pixbuf = gdk_pixbuf_new_from_file (sChemin, NULL); 
    GdkPixbuf *pixbuf_mini = NULL; 
    pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf,625, 450, 
	    GDK_INTERP_NEAREST); 
    pImage = gtk_image_new_from_pixbuf (pixbuf_mini);
    gtk_box_pack_start(GTK_BOX(p_hBox), pImage, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(p_vBox),p_hBox );
    gtk_widget_show_all(pWindow);



}

static void Binarize (void) {


    open_image("image2.bmp",p_hBox);

}



//static void menu_addWidget (GtkUIManager *  p_uimanager,GtkWidget * p_widget, GtkContainer * p_box)
static void menu_addWidget (GtkWidget * p_widget, GtkContainer * p_box)

{
    gtk_box_pack_start (GTK_BOX (p_box), (p_widget), FALSE, FALSE, 0);
    gtk_widget_show (p_widget);
    return;
}


static void menu_new (void)
{
    GtkWidget *pWindow;
    GtkWidget *pButton;
    GtkWidget *pFileSelection;
    GtkWidget *pDialog;
    gchar *sChemin;


    /* Creation de la fenetre de selection */
    pFileSelection = gtk_file_chooser_dialog_new("Enregistrer sous..",NULL ,GTK_FILE_CHOOSER_ACTION_SAVE,	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN, GTK_RESPONSE_OK,NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);

    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
	case GTK_RESPONSE_OK:
	    /* Recuperation du chemin */
	    sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
	    pDialog = gtk_message_dialog_new(GTK_WINDOW(pFileSelection),
		    GTK_DIALOG_MODAL,
		    GTK_MESSAGE_INFO,
		    GTK_BUTTONS_OK,
		    "Chemin du fichier :\n%s", sChemin);
	    gtk_dialog_run(GTK_DIALOG(pDialog));
	    gtk_widget_destroy(pDialog);
	    g_free(sChemin);
	    break;
	default:
	    break;
    }
    //	open_image(sChemin);

    gtk_widget_destroy(pFileSelection);



    return ;

}

static gchar *menu_open (void)
{
    GtkWidget *pWindow;
    GtkWidget *pButton;

    GtkWidget *pFileSelection;
    GtkWidget *pDialog;
    gchar *sChemin="";



    /* Creation de la fenetre de selection */
    pFileSelection = gtk_file_chooser_dialog_new("Ouvrir...",NULL ,GTK_FILE_CHOOSER_ACTION_OPEN,	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN, GTK_RESPONSE_OK,NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);

    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
	case GTK_RESPONSE_OK:
	    /* Recuperation du chemin */
	    sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
	    pDialog = gtk_message_dialog_new(GTK_WINDOW(pFileSelection),
		    GTK_DIALOG_MODAL,
		    GTK_MESSAGE_INFO,
		    GTK_BUTTONS_OK,
		    "Chemin du fichier :\n%s", sChemin);
	    gtk_dialog_run(GTK_DIALOG(pDialog));
	    gtk_widget_destroy(pDialog);

	    break;
	default:
	    break;
    }
    gtk_widget_destroy(pFileSelection);
    open_image(sChemin,p_vBox);
    g_free(sChemin);



    return sChemin ;

}

static void menu_quit (void)
{
    gtk_main_quit ();
    return;
}

static void menu_help (void)
{
    GtkWidget *p_dialog = NULL;

    p_dialog = gtk_message_dialog_new
	(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Aide");
    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
    return;
}
static void menu_about (void)
{
    GError *error = NULL;
    GIOChannel *channel = NULL;

    channel = g_io_channel_new_file ("licence.txt", "r", &error);
    if (channel != NULL)
    {
	char *text = NULL;

	if (g_io_channel_read_to_end (channel, &text, 0, &error) ==
		G_IO_STATUS_NORMAL)
	{
	    GtkWidget *p_dialog = gtk_about_dialog_new ();

	    gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (p_dialog),
		    "Exemple d'utilisation de GtkUIManager");
	    gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (p_dialog),
		    "Nicolas JOSEPH");
	    gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (p_dialog), text);
	    gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (p_dialog),
		    "http://nicolasj.developpez.com");
	    gtk_dialog_run (GTK_DIALOG (p_dialog));
	    g_free (text);
	    if (g_io_channel_shutdown (channel, FALSE, &error) ==
		    G_IO_STATUS_ERROR)
	    {
		GtkWidget *p_dialog = NULL;


		gtk_dialog_run (GTK_DIALOG (p_dialog));
		gtk_widget_destroy (p_dialog);
	    }
	}
    }
    if (error != NULL)
    {
	GtkWidget *p_dialog = NULL;

	gtk_dialog_run (GTK_DIALOG (p_dialog));
	gtk_widget_destroy (p_dialog);
    }
    return;
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

