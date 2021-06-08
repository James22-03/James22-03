#include <stdio.h>
#include <time.h>

#define TAM_NOMBRE 100
#define TAM_NUMEROS 1000000

int existe_archivo(char *nombre_arch);
int crear_archivo(char *nombre_arch);
void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch);
FILE *abrir_Archivo_lectura_escritura(char *nombre_arch);
int tiene_datos_arch(char *nombre_arch);
FILE *abrir_Archivo_solo_Lectura(char *nombre_arch);
void imprimir_vector(int vector[], int tam);
void ordBurbuja(int a[], int n);
int total_numeros_Arch(char *nombre_arch);

int main(int argc, char const *argv[]){
	clock_t start, end;
	double mili_segundos;
	double segundos;
	double minutos;
	// FILE es una estructura
	FILE *ptrCf = NULL;
	int existe_arch = 0, total_numeros = 0, numero_introducir = 0;
	//char nom_archivo[TAM_NOMBRE];
	int contador_numeros = 0;
	int numero_del_arch = 0;
	int vector[TAM_NUMEROS], i = 0;
	int numeros_desde_archivo = 0;

	do{
		//printf("\tIntroduzca el Nombre del Archivo a Crear: ");
		//gets(nom_archivo);
		//nom_archivo=argv[1];
		existe_arch = existe_archivo(argv[1]);
		if(existe_arch){
			printf("---------------------------------------------------------------\n");
			printf("\tEl archivo -> %s <- YA EXISTE.\n", argv[1]);
			printf("---------------------------------------------------------------\n");
		}
		else{
			printf("---------------------------------------------------------------\n");
			printf("\tEl archivo -> %s <- NO EXISTE.\n", argv[1]);
			printf("---------------------------------------------------------------\n");
			if(crear_archivo(argv[1])){
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\tEl archivo -> %s <- Fue creado EXITOSAMENTE.\n", argv[1]);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
			else{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\tEl archivo -> %s <- NO pudo crearse.\n", argv[1]);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}
	}while(existe_arch);
	do{
		printf("\tIntroduzca total de números a escribir sobre el Archivo -> %s <-: ", argv[1]);
		scanf("%d", &total_numeros);
		if(total_numeros < 1 || total_numeros > TAM_NUMEROS)
			printf("\t\t----> El total must be mayor a 0 y menor que %d\n", TAM_NUMEROS);
	}while(total_numeros < 1 || total_numeros > TAM_NUMEROS);
	ptrCf = abrir_Archivo_lectura_escritura(argv[1]);
	if(ptrCf == NULL){
		printf("****************************************************************\n");
		printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", argv[1]);
		printf("****************************************************************\n");
	}
	else{
		printf("****************************************************************\n");
		printf("\tArchivo -> %s <- Abierto Correctamente.\n", argv[1]);
		printf("****************************************************************\n");
		printf("----------------------------> ESCRITURA <----------------------------------\n");
		printf("--> (Unix - ^d para Terminar, Windows - ^z para Terminar) Introduzca número [%d]: ", i);
		scanf("%d", &numero_introducir);
		while(!feof(stdin)){
			fprintf(ptrCf, "%d\n", numero_introducir);
			i++;
			if(i == total_numeros){
				break;
			}
			printf("--> (Unix - ^d para Terminar, Windows - ^z para Terminar) Introduzca número [%d]: ", i);
			scanf("%d", &numero_introducir);
		}
		printf("\n");
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("\tEscritura Terminada.\n");
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		cerrar_archivo(ptrCf, argv[1]);
	}
	if(tiene_datos_arch(argv[1])){
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		printf("\tEL ARCHIVO -> %s <-TIENE DATOS.\n", argv[1]);
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		printf("------------------------------> LECTURA <----------------------------------\n");
		ptrCf = abrir_Archivo_solo_Lectura(argv[1]);
		if(ptrCf == NULL){
			printf("****************************************************************\n");
			printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", argv[1]);
			printf("****************************************************************\n");
		}
		else{
			printf("****************************************************************\n");
			printf("\tArchivo -> %s <- Abierto Correctamente.\n",argv[1]);
			printf("****************************************************************\n");
			printf("\t%s\n\n", "Números");
			// equivalente a la función scanf()
			fscanf(ptrCf, "%d", &numero_del_arch);
			while(!feof(ptrCf)){
				printf("\t-> [%d] = %d\n", contador_numeros, numero_del_arch);
				vector[contador_numeros] = numero_del_arch;
				contador_numeros++;
				fscanf(ptrCf, "%d", &numero_del_arch);
			}
			printf("\t Total de números leidos = %d\n\n", contador_numeros);
			imprimir_vector(vector, contador_numeros);
			printf("---------------------------------------------------------------------------\n");
			printf("\t---> LECTURA TERMINADA <---\n");
			printf("---------------------------------------------------------------------------\n");
			cerrar_archivo(ptrCf, argv[1]);
		}
		numeros_desde_archivo = total_numeros_Arch(argv[1]);
		printf("---------------------------------------------\n");
		printf("Ordenación por Burbuja.\n");
		printf("---------------------------------------------\n");
		printf("Lista original de %d elementos:\n\n", numeros_desde_archivo);
		imprimir_vector(vector, numeros_desde_archivo);
		start = clock();
		ordBurbuja(vector, numeros_desde_archivo);
		end = clock();
		printf("\n\t----> Ascedente <----\n");
		printf("Lista ordenada de %d elementos:\n\n", numeros_desde_archivo);
		imprimir_vector(vector, numeros_desde_archivo);
		segundos = ((double) (end - start)) / CLOCKS_PER_SEC;
      	mili_segundos = ( segundos / 0.001 );
      	minutos = ( segundos * 1 ) / 60;
      	printf("\n\tTiempo en seg = %lf s.\n", segundos);
      	printf("\tTiempo en mili_seg = %lf ms.\n", mili_segundos);
      	printf("\tTiempo en minutos = %lf min.\n", minutos);
      	printf("\n\tTotal de números leidos = %d.\n", numeros_desde_archivo);
	}
	else{
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
		printf("\tEL ARCHIVO -> %s <- NO TIENE DATOS.\n", argv[1]);
		printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	}
	printf("\n");
	return 0;
}

void ordBurbuja(int a[], int n){
	int interruptor = 1;
	int pasada, j, aux;
	for(pasada = 0; pasada < n-1 && interruptor; pasada++){
		interruptor = 0;
		for(j = 0; j < n-pasada-1; j++)
			if(a[j] > a[j+1]){
				interruptor = 1;
				aux = a[j];
				a[j] = a[j+1];
				a[j+1] = aux;
			}
	}
}

void imprimir_vector(int vector[], int tam){
	int i;
	for(i = 0; i < tam; i++){
		printf("%5d", vector[i]);
		if((i+1)%5 == 0)
			printf("\n");
	}
	printf("\n");
}

int total_numeros_Arch(char *nombre_arch){
	int lee_linea = 0, contador = 0;
	FILE *ptrArchivo;
	ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
	if(ptrArchivo == NULL){
		printf("El archivo -> %s <- NO se pudo abrir desde total_numeros().\n", nombre_arch);
	}
	else{
		printf("Archivo -> %s <- abierto desde total_numeros().\n", nombre_arch);
		// leo si hay datos
		fscanf(ptrArchivo, "%d", &lee_linea);
		// mientras no sea fin de archivo.
		while(!feof(ptrArchivo)){
			contador++;
			// leo si hay datos
			fscanf(ptrArchivo, "%d", &lee_linea);
		}
		cerrar_archivo(ptrArchivo, nombre_arch);
	}
	return contador;
}

int tiene_datos_arch(char *nombre_arch){
	int hay_Datos = 0;
	FILE *ptrArchivo;
	int lee_linea = 0, contador = 0;
	ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
	if(ptrArchivo == NULL){
		printf("El archivo -> %s <- NO se pudo abrir desde tiene_datos_arch().\n", nombre_arch);
		hay_Datos = 0;
	}
	else{
		printf("Archivo -> %s <- abierto desde tiene_datos_arch().\n", nombre_arch);
		// leo si hay datos
		fscanf(ptrArchivo, "%d", &lee_linea);
		// mientras no sea fin de archivo.
		while(!feof(ptrArchivo)){
			contador++;
			// leo si hay datos
			fscanf(ptrArchivo, "%d", &lee_linea);
			if(contador > 0){
				hay_Datos = 1;
				break;
			}
		}
		cerrar_archivo(ptrArchivo, nombre_arch);
	}
	return hay_Datos;
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

void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch){
	fclose(ptrArchivo);
	printf("----> Archivo -> %s <- Cerrado Correctamente.\n", nombre_arch);
}
