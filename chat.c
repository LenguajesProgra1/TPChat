#include "funciones.h"

// creacion de variables globales
char* inf;
GtkWidget *eMsj;
char *contacto;
char* txt[1];

char* enviar(GtkWidget *boton, GdkEventKey *event,GtkWidget *entry) // evento para enviar un mensaje al socket cliente
{
    gchar *str = NULL;
    int largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eMsj)), -1);
    if ( largo != 0)
    {     
        str = g_strconcat(contacto,":",gtk_entry_get_text(GTK_ENTRY(eMsj)),NULL);
        //char tkn[(sizeof(str))];
        //strcat(tkn,str);
        reg[3] = str;
        gtk_entry_set_text(GTK_ENTRY(eMsj),"");
        Cliente(3,reg);
    }
}


int chat(int argc,char *argv[],char *nom)//,char* info[])
{
    //creacion de la ventana para enviar mensajes
    contacto = nom;
    //inf = info;
    GtkWidget *window;
    gtk_init(&argc, &argv);
    GtkWidget *fixed;
    GtkWidget *bEnviar;
    GtkWidget *lTitulo;

  
    //Asignar los atributos a los punteros
    
    //Frame de inicio
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mensajeria");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 120);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    //Layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    //Botones
    bEnviar = gtk_button_new_with_label("Enviar");
    gtk_fixed_put(GTK_FIXED(fixed), bEnviar, 135, 80);
    gtk_widget_set_size_request(bEnviar, 80, 35);
    
    //Labels
    lTitulo = gtk_label_new("Escriba su mensaje:");
    gtk_fixed_put(GTK_FIXED(fixed), lTitulo, 100, 0);
    gtk_widget_set_size_request(lTitulo, 150, 35);

    
    //Entry
    eMsj = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), eMsj, 100, 40);
    gtk_widget_set_size_request(eMsj, 100, 30);
    
    //Declaracion de señales
    g_signal_connect(G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(bEnviar), "clicked", G_CALLBACK(enviar), NULL);
    gtk_widget_show_all(window);
        
    gtk_main();
    return 0;
}
