#include "funciones.h"

GtkWidget *eNombre,*window;
int puerto;
int caracter;
char ipser[16];

void Registrar (gchar* usuario)
{
    char temp[20];
    char reg[4];
    reg[0]= '3';
    snprintf(temp,(sizeof(temp)),"%s",ipser);
    bzero(temp,20);
    sprintf(temp,"%d",caracter);
    reg[2]= "192.168.0.143";
    bzero(temp,20);
    sprintf(temp,"%d",usuario);
    reg[3]= temp;
    bzero(temp,20);
    Cliente(3,&reg);
}

void Validacion (GtkWidget *boton, GdkEventKey *event)//Validacion del entry del frame principal
{
   int largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eNombre)), -1);
   if ( largo != 0)
    {
        gchar *str = NULL;
        str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(eNombre)), NULL);
        Registrar(str);
    }
   else
    g_print("Debe ingresar su nombre de usuario\n");
   
}

int main(int argc, char** argv) {
    
    FILE *f = fopen("puerto.txt","r");//Se lee el archivo del puerto
    fscanf(f,"%d",&caracter);//puerto	
    fclose(f);
    
    f = fopen("ipServidor.txt","r");//Se lee el archivo de la ip del servidor
    fgets(ipser,16,f);//ip	
    fclose(f);
    
// Declaracion de los punteros de interfaz
    GtkWidget *fixed;
    GtkWidget *bSesion;
    GtkWidget *lTitulo;
    GtkWidget *lNombre;
    gtk_init(&argc, &argv);
    //Asignar los atributos a los punteros
    
    //Frame de inicio
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chat");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 120);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    //Layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    //Botones
    bSesion = gtk_button_new_with_label("Iniciar Sesion");
    gtk_fixed_put(GTK_FIXED(fixed), bSesion, 135, 80);
    gtk_widget_set_size_request(bSesion, 80, 35);
    
    //Labels
    lTitulo = gtk_label_new("Inicio de Sesion");
    gtk_fixed_put(GTK_FIXED(fixed), lTitulo, 100, 0);
    gtk_widget_set_size_request(lTitulo, 150, 35);
    lNombre = gtk_label_new("Usuario :");
    gtk_fixed_put(GTK_FIXED(fixed), lNombre, 10, 35);
    gtk_widget_set_size_request(lNombre, 55, 35);
    
    //Entry
    eNombre = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), eNombre, 100, 40);
    gtk_widget_set_size_request(eNombre, 80, 20);
    
    //Declaracion de señales
    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(bSesion), "clicked", G_CALLBACK(Validacion), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
