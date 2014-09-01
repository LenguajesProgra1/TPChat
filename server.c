#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/socket.h> 

#include <netinet/in.h>

#include <sys/unistd.h>

#include <arpa/inet.h>

FILE* f;

void dostuff(int); 

void error(const char *msg)
{
    perror(msg); 
	exit(1);
}

int main(int argc, char *argv[])
{
	f	= fopen("Contactos","a+");
	int sockfd, newsockfd, portno, pid; 
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no hay ningún puerto\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)

		error("ERROR de apertura de socket"); 
	
	bzero((char *) &serv_addr, sizeof(serv_addr)); 
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		
		error("ERROR en la conexión");

	listen(sockfd,5); 
	clilen = sizeof(cli_addr);

	while (1) 
	{
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) 

			error("ERROR en aceptar"); 
		
		pid = fork();

		if (pid < 0) 

			error("ERROR en fork");

		if (pid == 0)
		{ 
			close(sockfd); 
			dostuff(newsockfd); 
			exit(0);
		} 
		else
			close(newsockfd);
	} 
	close(sockfd); 
	return 0; 
}

void dostuff (int sock)
{
	int n,len_inet; 
	char buffer[256], ip[14]; 
	struct sockaddr_in addr_inet;    

	getpeername(sock, (struct sockaddr *)&addr_inet, &len_inet);
	snprintf(ip,(sizeof(ip)), "%s", (inet_ntoa(addr_inet.sin_addr)));  	

	bzero(buffer,256);
	n = read(sock,buffer,255);
	if (n < 0)
		error("ERROR al leer del socket");
	
	if(buffer[0]=='&')
	{
		
		fprintf(f,"%s:%s\n",buffer,ip);
	}

	printf("Aquí está el mensaje: %s\n",buffer); 
	n = write(sock,"Tengo el mensaje",18); 
	if (n < 0)
		error("ERROR al escribir en el socket"); 
}
