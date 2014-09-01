#include "funciones.h"

// creacion de variables globales
GtkWidget* textArea;
GtkWidget* boton;
GtkWidget* textEntry;
GtkTextBuffer *buffer;
GtkTextIter start, end;
GtkTextIter iter;
char *contacto;
char* txt[1];

char* enviado(GtkWidget *boton, GdkEventKey *event,GtkWidget *entry) // evento para enviar un mensaje al socket cliente
{
    // manejo de variables de la libreria gtk para mostrar el texto ingresado en el frame
    const gchar* texto; 
    
    txt[0] = g_strconcat(contacto,gtk_entry_get_text(GTK_ENTRY(entry)),NULL);
    texto = gtk_entry_get_text(GTK_ENTRY(entry));
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, texto , -1);
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, " \n " , -1);
    gtk_entry_set_text(GTK_ENTRY(textEntry),"");
    return txt[0];
}

GtkWidget* chatFrame()// crea el frame para el chat
{
// manejo de variables de la libreria gtk para crear el chatFrame
    
textEntry = gtk_entry_new();
textArea = gtk_text_view_new();
GtkWidget* scrollbar= gtk_vscrollbar_new(gtk_text_view_get_vadjustment(GTK_TEXT_VIEW(textArea)));
GtkWidget* console = gtk_table_new(3, 2, FALSE);
gtk_text_view_set_editable(G_OBJECT(textArea),0);
boton = gtk_button_new_with_label("Enviar");
gtk_table_attach_defaults(GTK_TABLE(console), textArea, 0, 4, 0, 1);
gtk_table_attach_defaults(GTK_TABLE(console), scrollbar, 0, 4, 0, 1);
gtk_table_attach_defaults(GTK_TABLE(console), textEntry, 0, 3, 1, 2);
gtk_table_attach_defaults(GTK_TABLE(console), boton, 3,4,1,2);
gtk_widget_set_size_request(textArea, 320, 240);
gtk_widget_grab_focus(textEntry);
return console;
}

int chat(int argc,char* argv[],char *nom)
{
    //creacion del frame principal sobre el que se va a encontrar la ventana para enviar mensajes
    contacto = nom;
    GtkWidget *window;
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mensajeria");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(window), chatFrame());
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT(boton), "clicked",G_CALLBACK(enviado), G_OBJECT(textEntry));
    gtk_main();
    return 0;
}
