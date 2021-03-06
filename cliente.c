#include "funciones.h"

void errorCli(const char *msg)
{ 
    perror(msg); 
    exit(0); 
}

int Cliente(int argc, char *argv[])
{
    int sockfd, portno, n,existe; 
    struct sockaddr_in serv_addr; 
    struct hostent *server;

    char buffer[256]; 
    if (argc < 3)
    { 
        fprintf(stderr,"El puerto host %s está en uso\n", argv[0]); 
        exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)

        error("ERROR de apertura de socket");

    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no hay host \n"); 
        exit(0); 
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)        
        error("ERROR de conexión"); 

    bzero(buffer,256);
    //fgets(buffer,255,stdin);
    //buffer = argv[3];

    n = write(sockfd,argv[3],(strlen(argv[3])));

    if (n < 0)
        error("ERROR al escribir en socket");

    bzero(buffer,256);
    n = read(sockfd,buffer,255);

    if (n < 0)
        error("ERROR al leer del socket");
    
    existe = buffer[0]-'0';
    
    close(sockfd); 
    
    return existe;
}
