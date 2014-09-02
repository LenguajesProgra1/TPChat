/* 
 * File:   funciones.h
 * Author: mariana
 *
 * Created on 19 de agosto de 2014, 06:35 PM
 */

#ifndef FUNCIONES_H
#define	FUNCIONES_H
#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#ifdef	__cplusplus
extern "C" {
#endif

void Agregar (GtkWidget*, GdkEventKey*);
int Interfaz(int, char**);//,char* info[]);
GtkWidget* chatFrame();
int chat(int,char* argv[],char*);//,char* info[]);
char* enviado(GtkWidget *, GdkEventKey *,GtkWidget *);
void errorInter (GtkWidget *, GdkEventKey *, GtkWidget *);
char *reg[3];

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCIONES_H */
