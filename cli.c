#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
#define MAX 100
#define SA struct sockaddr
void func(int sockfd){
	char buff1[MAX],buff2[MAX];
	int n;
	int sum[MAX];
		//Solicita al cliente el primer numero
		bzero(buff1, sizeof(buff1));
		printf("Ingrese el numero 1: ");
		n = 0;
		while ((buff1[n++] = getchar()) != '\n');
		
		//Envia el primer numero al servidor
		write(sockfd, buff1, sizeof(buff1));
		
		//Solicita al cliente el segundo numero
		bzero(buff2, sizeof(buff2));
		printf("Ingrese el numero 2: ");
		n = 0;
		while ((buff2[n++] = getchar()) != '\n');
		//Envia el primer numero al servidor
		write(sockfd, buff2, sizeof(buff2));
		
		//Imprime el resultado que envia el servidor
		//bzero(sum, MAX);
		read(sockfd, sum, sizeof(sum));
		printf("Desde servidor resultado = %i\n", sum);
}

//Funcion principal
int main(int argc, char *argv[]){
	int sockfd, connfd,port;
	
	struct sockaddr_in servaddr, cli;
	
	//En caso de no especifiar el puerto al ejecutar el programa se le pida al usuario que lo ingrese
	if (argc <2){
		port=PORT;
		printf("No indico un puerto por defecto se asigno PORT = %i\n",port);
		printf("Direccion IP = 127.0.0.1\n");
	}else{
		port=atoi(argv[1]);
		printf("Indico el puerto PORT = %i\n",port);
		printf("Direccion IP = 127.0.0.1\n");	
	}
	// Creacion y verificacion del socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Creacion del socket fallida...\n");
		exit(0);
	}
	else
		printf("Creacion exitosa del socket..\n");
	bzero(&servaddr, sizeof(servaddr));

	// Asignación del direccion IP y puerto
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Conexion del cliente con el servidor
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("La conexion con el servidor ha fallado...\n");
		exit(0);
	}
	else
		printf("Cliente conectado al servidor...\n");

	// Funcion para ingresar los numeros
	func(sockfd);

	// Cierra el socket
	close(sockfd);
}

