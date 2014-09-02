#include "funciones.h"

GtkWidget *eNombre,*window,*help;// declaracion de variables
int caracter;

void Validacion (GtkWidget *boton, GdkEventKey *event, GtkWidget *entry)//Validacion del entry del frame principal
{
    int registro;
    int largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eNombre)), -1);
    if ( largo != 0)
    {
        gchar *str = NULL;
        str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(eNombre)), NULL);
        char tkn[(sizeof(str)+1)]={'&'};
        strcat(tkn,str);
        reg[3] = tkn;
        registro = Cliente(3,reg);//envio de parametros
        if(registro==1)
        {
            gtk_widget_destroy(help);
            entry = Interfaz(0,0);
        }
        else
        {
            g_print("Ya existe ese nombre de usuario\n");
            gtk_entry_set_text(GTK_ENTRY(eNombre),"");
        }
    }
   else
    g_print("Debe ingresar su nombre de usuario\n");
}

int main(int argc, char** argv) 
{    
    int pid,bandera=0;
    pid = fork();
    while(1)
    {
        if(pid<0)
            g_print("ERROR en fork");
        if(pid==0)
        {
            if(bandera==0)
            {
                bandera=1;
                servidor(3,15557);
            }
        }
        else
        {
            char tmp[14];
            char temporal[6];
            FILE *f;

            reg[0] = "3";

            f = fopen("ipServidor.txt","r");
            fgets(tmp,14,f);
            reg[1] = tmp;    
            fclose(f);    

            f = fopen("puerto.txt","r");
            fgets(temporal,6,f);
            reg[2] = temporal;    
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

            help = window;

            gtk_main();
            return 0;
            }
    }
}
