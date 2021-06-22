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

// Funcion que suma dos numeros grandes
void func(int sockfd){
	char buff1[MAX]; //Amacena en primer numero ingresado como caracteres
	char buff2[MAX]; //Almacena el segundo numero ingresado como caracteres
	int num1[MAX],num2[MAX],sum[MAX]; //Almacenarán los numeros y el resultado como enteros
	int l1,l2,n; //variables auxiliares
		bzero(buff1, MAX);
		// lee el primer numero que envia el cliente
		read(sockfd, buff1, sizeof(buff1));
		// imprime el numero que envia el cliente
		printf("Numero 1 de cliente: %s\n", buff1);
		
		bzero(buff2, MAX);
		// lee el segundo numero que envia el cliente
		read(sockfd, buff2, sizeof(buff2));
		// pimprime el numero
		printf("Numero 2 de cliente: %s\n", buff2);

	//Convierte la cadena ingresada a enteros	
	for (l1 = 0; buff1[l1] != '\0'; l1++)
	num1[l1] = buff1[l1] - '0';

	for (l2 = 0; buff2[l2] != '\0'; l2++)
	num2[l2] = buff2[l2] - '0';
	
	//Variables auxiliares
	int carry = 0;
	int k = 0;
	int i = l1 - 1;
	int j = l2 - 1;
	
	//Proceso de suma
	for (; i >= 0 && j >= 0; i--, j--, k++) {
		sum[k] = (num1[i] + num2[j] + carry) % 10;
		carry = (num1[i] + num2[j] + carry) / 10;
	}
	if (l1 > l2) {
		while (i >= 0) {
		sum[k++] = (num1[i] + carry) % 10;
		carry = (num1[i--] + carry) / 10;
		}
	} else if (l1 < l2) {
		while (j >= 0) {
		sum[k++] = (num2[j] + carry) % 10;
		carry = (num2[j--] + carry) / 10;
		}
	} else {
		if (carry > 0)
		sum[k++] = carry;
	}
	
	//Imprime el resultado
	printf("Resultado de la suma: ");
	for (k--; k >= 0; k--)
	printf("%d", sum[k]);
	printf("\n");
	
	//Lo envia al cliente	
	bzero(sum, MAX);
	write(sockfd, sum, sizeof(sum));	
}

// Funcion principal
int main(int argc, char *argv[]){
	int sockfd,connfd,len,port;
	struct sockaddr_in servaddr, cli;
	
	//En caso de no especifiar el puerto al ejecutar el programa se le pida al usuario que lo ingrese
	if (argc <2){
		port=PORT;
		printf("No indico un puerto por defecto se asigno PORT = %i\n",port);
	}else{
		port=atoi(argv[1]);
		printf("Indico el puerto PORT = %i\n",port);
	}
	// Creacion y verificacion del socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("La creación del socket ha fallado...\n");
		exit(0);
	}
	else
		printf("Socket creado exitosamente...\n");
	bzero(&servaddr, sizeof(servaddr));

	// Asignacion de puerto y dirección IP
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	// Vinculacion del socket creado con la dirección IP y verificación
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Enlace del socket ha fallado...\n");
		exit(0);
	}
	else
		printf("Socket vinculado correctamente...\n");

	//Poner al servidor en modo escucha
	if ((listen(sockfd, 5)) != 0) {
		printf("El modo escucha ha fallado...\n");
		exit(0);
	}
	else
		printf("Servidor en espera...\n");
	len = sizeof(cli);

	// Acceptar y verificar la conexión del cliente
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("La conexion con el cliente ha fallado...\n");
		exit(0);
	}
	else
		printf("Conexion aceptada...\n");

	// Llamada a la funcion que realiza la suma
	func(connfd);

	// Terminada la suma se cierra el socket
	close(sockfd);
}
