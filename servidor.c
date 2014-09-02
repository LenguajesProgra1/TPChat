#include "servidor.h"

FILE* f;
char *reg[3];
int port;
char puerto[5];

void error(const char *msg){
    perror(msg); 
	exit(1);
}

int main(int argc, char *argv[])
{
	
	int sockfd, newsockfd, pid, portno;
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
	port=portno;
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
			f	= fopen("Contactos","a+");
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
	int n,len_inet,existe=0; 
	char buffer[256], ip[14], linea[30]; 
	char *token, *nom, *buf, *string;
	char  *ipCon, *msj;
	struct sockaddr_in addr_inet;  

	getpeername(sock, (struct sockaddr *)&addr_inet, &len_inet);
	snprintf(ip,(sizeof(ip)), "%s", (inet_ntoa(addr_inet.sin_addr)));  	

	bzero(buffer,256);
	n = read(sock,buffer,255);

	if (n < 0)
		error("ERROR al leer del socket");

	buf = strdup(buffer);	
	nom = strsep(&buf,":");
	
	if(buffer[0]=='&')
	{
		while(!feof(f))
		{
			if(fgets(linea,30,f))
			{
				string = strdup(linea);
				token = strsep(&string,":");
				
				if((strcmp(token,nom))!=0)
				{
					existe=0;
				}
				if((strcmp(token,nom))==0)
				{
					existe=1;
					break;
				}
			}
		}
		if (!existe)
		{
			fprintf(f,"%s:%s\n",buffer,ip);
			n = write(sock,"1",3); 
		}
		else
			n = write(sock,"0",3); 
	}

	if(buffer[0]!='&')
	{
		char tkn[(sizeof(nom)+1)]={'&'};
		strcat(tkn,nom);
		msj = strsep(&buf,":");
		while(!feof(f))
		{
			if(fgets(linea,30,f))
			{
				string = strdup(linea);
				token = strsep(&string,":");
				if((strcmp(token,tkn))!=0)
				{
					existe=0;
				}
				if((strcmp(token,tkn))==0)
				{
					existe=1;
					break;
				}
			}
		}
		if (existe==1)
		{
			ipCon = (strsep(&string,"\n"));
			reg[0]="3";
			reg[1]=ipCon;
			reg[2] = "15557";
			reg[3]=msj;
			cliente(3,reg);
			return;
		}
		if (existe==0)
			printf("No existe ese usuario");
	}
}
