#include "funciones.h"
//char* inf;
GtkWidget *eContact;
GtkWidget *window;

void errorInter (GtkWidget *boton, GdkEventKey *event, GtkWidget *entry)//Validacion del entry del frame chat
{
   int largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eContact)), -1);
   if ( largo != 0)
    {
        gchar *str = NULL;
        //char* mensaje;
        str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(eContact)), NULL);
        gtk_entry_set_text(GTK_ENTRY(eContact),"");
        entry = chat(0,0,str);
    }
   else
    g_print("Debe ingresar el nombre del contacto\n");
}

int Interfaz (int argc, char **argv)//,char* info[])
{
    //inf = info;
    GtkWidget *vbox;
    GtkWidget *bArch;
    GtkWidget *bMsj;
    GtkWidget *lCont;


    gtk_init(&argc, &argv); // manejo de interfaz
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Chat");
    gtk_widget_set_size_request (window, 200, 300);
    vbox = gtk_vbox_new(FALSE, 2);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    bMsj = gtk_button_new_with_label("Enviar mensaje");
    bArch = gtk_button_new_with_label("Enviar archivo");
    lCont = gtk_label_new("Contacto:");
    eContact = gtk_entry_new();
    
    gtk_box_pack_start(GTK_BOX(vbox), lCont, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), eContact, FALSE, FALSE, 1);    
    gtk_box_pack_start(GTK_BOX(vbox), bMsj, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), bArch, FALSE, FALSE, 1);
    
    g_signal_connect(G_OBJECT(bMsj), "clicked",G_CALLBACK(errorInter) ,NULL);
    g_signal_connect(G_OBJECT(bArch), "clicked",G_CALLBACK(errorInter) ,NULL);
    g_signal_connect(G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
        
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
