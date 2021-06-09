#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variables que reciben los argumentos el linea de comandos
char *nombre;
char *nombre2;

//Declaración de funciones
int existe_archivo(char *nombre_arch); //Comprueba si los archivos existen.
int crear_archivo(char *nombre_arch); //Crear un archivo en caso de no existir.
void liberar(); //Libera 
void insertar(); //Inserta las cdenas en la lista
void imprimir(); //Ordena alfabeticamente cada palabra y las imprime.
int vacia(); //Comprueba si la lista esta vacia
void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch); //Cierra un fichero una vez terminada su utilidad
FILE *abrir_Archivo_solo_Lectura(char *nombre_arch); //Abre un archivo de solo lectura qie contine la lista de cadenas sin ordenar
FILE *abrir_Archivo_lectura_escritura(char *nombre_arch); //Abre/crea un archivo para insertar la lista ordenada

//Estructura para insertar elementos a la lista
struct nodo {
	char cadena[50];
	struct nodo *sig;
};

struct nodo *raiz=NULL;

int main (int argc, char *argv[]){
FILE *ptrCf = NULL,*g = NULL;
//Argumentos para los archivos de entrada y salida
nombre=argv[1];
nombre2=argv[2];

int existe_arch = 0,i;
existe_arch = existe_archivo(nombre);
if(existe_arch){
	printf("---------------------------------------------------------------\n");
	printf("\tEl archivo -> %s <- YA EXISTE.\n", nombre);
	printf("---------------------------------------------------------------\n");
	}else{
		printf("---------------------------------------------------------------\n");
		printf("\tEl archivo -> %s <- NO EXISTE.\n", nombre);
		printf("---------------------------------------------------------------\n");
		if(crear_archivo(nombre)){
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\tEl archivo -> %s <- Fue creado EXITOSAMENTE.\n", nombre);	
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}else{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\tEl archivo -> %s <- NO pudo crearse.\n",nombre);			
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
			}
		ptrCf = abrir_Archivo_solo_Lectura(nombre);
		if(ptrCf == NULL){
			printf("****************************************************************\n");
			printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", nombre);			
			printf("****************************************************************\n");
		}
		else{
			printf("****************************************************************\n");
			printf("\tArchivo -> %s <- Abierto Correctamente.\n", nombre);			
			printf("****************************************************************\n");
		ptrCf = abrir_Archivo_lectura_escritura(nombre);
		if(ptrCf == NULL){
		printf("****************************************************************\n");
		printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", nombre);			
		printf("****************************************************************\n");
		}
		else{
		printf("****************************************************************\n");
		printf("\tArchivo -> %s <- Abierto Correctamente.\n", nombre);			
		printf("****************************************************************\n");		
		printf("----------------------------> ESCRITURA <----------------------------------\n");
		//Creación de la lista en el archivo de entrada
		fprintf(ptrCf,"Me entere que estaban buscando personal a traves del grupo embedidos32.");	
		}	
		printf("\tEscritura Terminada.\n");
		cerrar_archivo(ptrCf, nombre);
		}
		ptrCf = abrir_Archivo_lectura_escritura(nombre2); //Es necesario que el archivo exista
		if(ptrCf == NULL){
		printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", nombre2);
		}
		else{
		printf("\tArchivo -> %s <- Abierto Correctamente.\n", nombre2);		
		printf("----------------------------> ESCRITURA <----------------------------------\n");
		//Ordenamiento de la lista en el archivo de salida
		insertar("Me");
		insertar("entere");
		insertar("que");
		insertar("estaban");
		insertar("buscando");
		insertar("personal");
		insertar("a");
		insertar("traves");
		insertar("del");
		insertar("grupo");
		insertar("embedidos32.");
		
		imprimir();
		//Impresión de la lista ordenada en pantalla
		struct nodo *reco=raiz;
		while (reco != NULL){
		fprintf(ptrCf,"%s\n",reco->cadena);
		reco=reco->sig;
		}
		printf("\n");	
		printf("\tEscritura Terminada.\n");
		cerrar_archivo(ptrCf, nombre2);
		}	
		return 0;
}


int existe_archivo(char *nombre_arch){
	FILE *ptrArchivo;
	int existe = 0;
	// Con r abre un archivo para lectura.
	ptrArchivo = fopen(nombre_arch, "r");
	if( ptrArchivo != NULL ){
		existe = 1;
		cerrar_archivo(ptrArchivo, nombre_arch);
	}	
	return existe;
}

int crear_archivo(char *nombre_arch){
	int creado = 0;
	FILE *ptrArchivo;
	ptrArchivo = fopen(nombre_arch, "w");
	if( ptrArchivo == NULL ){
		// con w crea un archivo para escritura. Si el archivo ya existe, descarta el contenido actual.
		printf("----> El archivo -> %s <- no pudo crearse (abrir; uso de w).\n", nombre_arch);
	}	
	else{
		creado = 1;
		printf("----> Archivo -> %s <- Creado (abierto; uso de w).\n", nombre_arch);
		cerrar_archivo(ptrArchivo, nombre_arch);
	}
	return creado;
}

void liberar (){
	struct nodo *reco = raiz;
	struct nodo *bor;
	while (reco != NULL){
		bor = reco;
		reco = reco->sig;
		free(bor);
	}	
}

int vacia(){
	if (raiz == NULL)
		return 1;
	else
		return 0;
}

void imprimir(){
	struct nodo *reco=raiz;
	while (reco != NULL){
		printf("%s\n",reco->cadena);
		reco=reco->sig;
	}
	printf("\n");
}

void insertar(char *x){
	struct nodo *nuevo;
	nuevo=malloc(sizeof(struct nodo));
	strcpy(nuevo->cadena,x);
	nuevo->sig=NULL;
	if(raiz==NULL){
		raiz=nuevo;
	}else{
		if (strcmp(x,raiz->cadena)<0){
			nuevo->sig=raiz;
			raiz=nuevo;
		}else{
			struct nodo *reco=raiz;
			struct nodo *atras=raiz;
			while (strcmp(x,reco->cadena)>0 && reco->sig !=NULL){
				atras=reco;
				reco=reco->sig;
			}
			if(strcmp(x,reco->cadena)>0){
				reco->sig=nuevo;
			}else{
				nuevo->sig=reco;
				atras->sig=nuevo;
			}
		}
	}
}

FILE *abrir_Archivo_solo_Lectura(char *nombre_arch){
	FILE *ptrArchivo;
	ptrArchivo = fopen(nombre_arch, "r");
	if( ptrArchivo == NULL ){
		// con r Abre un archivo para lectura.
		printf("---> El archivo -> %s <- NO pudo abrirse (uso de r).\n", nombre_arch);
	}	
	else{
		printf("---> Archivo -> %s <- Abierto (uso de r).\n", nombre_arch);
	}
	return ptrArchivo;
}

FILE *abrir_Archivo_lectura_escritura(char *nombre_arch){
	FILE *ptrArchivo;
	ptrArchivo = fopen(nombre_arch, "r+");
	if( ptrArchivo == NULL ){
		// con r+ Abre un archivo para actualización (lectura y escritura).
		printf("---> El archivo -> %s <- NO pudo abrirse (uso de r+).\n", nombre_arch);
	}	
	else{
		printf("---> Archivo -> %s <- Abierto (uso de r+).\n", nombre_arch);
	}
	return ptrArchivo;
}

void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch){
	fclose(ptrArchivo);
	printf("----> Archivo -> %s <- Cerrado Correctamente.\n", nombre_arch);
}
