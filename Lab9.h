#ifndef stdio_h
#include <stdio.h>
#define stdio_h
#endif

#ifndef stdlib_h
#include <stdlib.h>
#define stdlib_h
#endif

#ifndef time_h
#include <time.h>
#define time_h
#endif

#ifndef string_h
#include "string.h"
#define string_h
#endif

typedef struct Tnodo{
    char *palabra;
    int totalDePalabras;
    struct Tnodo *sgte;
}Nodo,*ptrNodo;


int maximo(Nodo* tablaHash[], int tamTabla);
int minimo(Nodo *tablaHash[],int tamTabla);
int promedio(Nodo *tablaHash[], int tamTabla);
int busqueda(Nodo* tablaHash[],char *palabra,int tamTabla);
void liberarMemoria(Nodo* tablaHash[], int tamTabla);
void iniciarTabla(Nodo *tablaHash[],int tamTabla);
unsigned int operacionHash(char *palabra,int tamTabla);
Nodo *crearNodo(char *palabra);
void creatablahash(Nodo* tablaHash[],char *palabra, int tamTabla);
int leerArchivo(Nodo* tablaHash[],char *nombre, int tamTabla);
void insertarPalabra(Nodo *tablaHash[],char *palabra,int tamTabla);

void crearArchivoParaMostrar(Nodo *tablaHash[], int tamTabla){
	FILE *archivo = fopen("NuevoArchivo.txt","w");
	Nodo *nodoAux;
	fprintf(archivo,"Tabla Hash\n-----------------\n");
	for(int cont=0; cont<tamTabla; cont++){
	    nodoAux = tablaHash[cont];
		fprintf(archivo,"%i]: ",cont);
		while(nodoAux){
			fprintf(archivo,"[%s] -> ",nodoAux->palabra);
			nodoAux = nodoAux->sgte;
		}
		fprintf(archivo,"\n\n");
	}
	fclose(archivo);
}


int busqueda(Nodo* tablaHash[],char *palabra,int tamTabla){
    Nodo *nodoAux;
    int resultado = 1;
    for(int cont=0; cont< tamTabla; cont++){
        nodoAux = tablaHash[cont];
        while(nodoAux){
            if(strcmp(palabra,nodoAux->palabra) != 0){
                nodoAux = nodoAux->sgte;
            }else{
                resultado = 0;
                return resultado;
            }
        }

    }
    free(nodoAux);
    return resultado;
}

void liberarMemoria(Nodo* tablaHash[], int tamTabla){
    for(int cont=0; cont<tamTabla; cont++){
        Nodo *nodoAux;
        while(tablaHash[cont]){ //Mientras la tabla no este nula
            nodoAux = tablaHash[cont]; //nodoAus a punta al primer nodo de la posicion cont
            tablaHash[cont] = nodoAux->sgte;//Entonces tablaHash apunta al sgte nodo de la posicion cont
            free(nodoAux); //Se libera la memoria del primer nodo
        }
        tablaHash[cont] = NULL; //Al final como la listas se eliminaron, la posicion apunta a nulo
    }

}

void iniciarTabla(Nodo *tablaHash[],int tamTabla){
    for(int cont=0; cont<tamTabla; cont++){
        tablaHash[cont] = NULL; //Iniciamos la tabla pero en nulo, tambien puede declarar 0 por si hay error
    }
}

int maximo(Nodo *tablaHash[],int tamTabla){
    int maximoDePalabras = 0; 
    int cantidadDePalabras = 0; //Variables para el maximo y la cantidad total de palabras que hay en la posicion
    Nodo *nodoAux;
    for(int cont=0; cont<tamTabla;cont++){
        nodoAux = tablaHash[cont]; //Un nodo apunta a la tabla, es decir al primero nodo de la posicion que dice cont
        while(nodoAux){ //Mientras nodo no es nulo
            cantidadDePalabras++; //Aumenta
            nodoAux = nodoAux->sgte; //Se mueve de un nodo a otro en la lista
        }
        if(maximoDePalabras < cantidadDePalabras){ //Si maximo es menor que la cantidad de palabras
            maximoDePalabras = cantidadDePalabras; //Maximo obtiene el valor de totalDePalabras
        }
        cantidadDePalabras = 0; //Vuelve a ser 0 para poder usarse nuevamente
    }
    free(nodoAux);

    return maximoDePalabras;
}

int minimo(Nodo *tablaHash[],int tamTabla){
    int minimo = 100000; //Le damos un valor grande para comparar despues
    int cantidadDePalabras = 0;
    Nodo *nodoAux;
    for(int cont=0; cont<tamTabla; cont++){
        nodoAux = tablaHash[cont]; /*La funcion es igual a maximo*/
        while(nodoAux){
            cantidadDePalabras++;
            nodoAux = nodoAux->sgte;
        }
        if(minimo > cantidadDePalabras){ //Solo cambia esta condicion, para que minimo obtenga la menor cantidad
            minimo = cantidadDePalabras;
        }
        cantidadDePalabras = 0;
    }
    free(nodoAux);
    return minimo;
}

int promedio(Nodo *tablaHash[], int tamTabla){
    float promedio; 
    promedio = tablaHash[0]->totalDePalabras/tamTabla;
    /*Como se guardo el total de palabras en la estructura, lo usamos para que el tamano de la tabla lo divida*/
    /*Asi que se saca un promedio de palabras que hay por posicion de la tabla*/
    return promedio;
}

unsigned int operacionHash(char *palabra,int tamTabla){
    int largo;
    largo = strlen(palabra);
    unsigned int resultadoHash = 0; //unsigned nos permite que no se utilicen los valores negativos, por ende se puede usar valores más grandes
    for(int cont=0; cont<largo; cont++){
        resultadoHash = resultadoHash*131 + *(palabra + cont);
    }
    resultadoHash = resultadoHash%tamTabla; //metodo hash division

    return resultadoHash;

}

Nodo *crearNodo(char *palabra){
    int largo = strlen(palabra); //Strlen permite obtener el largo de un string sin contar \0, ej: hola, su largo seria 4
    Nodo *nodoAux = (Nodo *)malloc(sizeof(struct Tnodo));
    nodoAux->sgte = NULL;
    nodoAux->palabra = (char *)malloc(sizeof(char)*(largo+1)); //Pedir memoria de tipo char para poder hacer un arreglo con el largo+1 para \0
    strcpy(nodoAux->palabra,palabra); //Copia el string de palabra y la guarda en el string de la estructura

    return nodoAux; //retornamos el nodo
}

//Funcion para agregar el nodo a la tabla y a la lista
void insertarPalabra(Nodo *tablaHash[],char *palabra,int tamTabla){ 
    //Recordar que palabra es la palabra extraida del archivo
    int resultadoHash;
    Nodo *nodoAux1; Nodo *nodoAux2;
    resultadoHash = operacionHash(palabra,tamTabla); //resultadoHash resibe la clave (posicion) donde se guardara
    nodoAux1 = tablaHash[resultadoHash]; //nodoAux1 guarda el puntero a la tabla
    nodoAux2 = crearNodo(palabra); //se crea el nodoAux2 con la nueva palabra
    tablaHash[resultadoHash] = nodoAux2; //la tabla apunta al nodo nuevo
    tablaHash[resultadoHash]->sgte = nodoAux1; //Tabla hash su sgte contiene el puntero de la tabla que la tenia nodoAux
}


//Funcion que retorna la cantidad total de palabras procesadas
int leerArchivo(Nodo* tablaHash[],char *nombre, int tamTabla){
    strcat(nombre,".txt"); //Agrega .txt despues del ultimo caracter del string
    char *palabraExtraida;
    int totalDePalabras = 0;
    FILE *archivo = fopen(nombre,"r");
    while(!feof(archivo)){ //Mientras no sea final de archivo
        palabraExtraida = (char *)malloc(sizeof(char)*30);
        fscanf(archivo,"%s",palabraExtraida);//Copia el string del archivo y la deja en el string palabraextraida
        insertarPalabra(tablaHash,palabraExtraida,tamTabla);//Ingresa la palabra al nuevo nodo
        totalDePalabras++;
        free(palabraExtraida);
    }
    fclose(archivo);
    tablaHash[0]->totalDePalabras = totalDePalabras; //Se guarda el total de palabras en la estructura, pero solo en la primera posicion
    return totalDePalabras;
}

void creatablahash(Nodo* tablaHash[], char *nombre, int tamTabla){
    int cantidadPalabras;
    iniciarTabla(tablaHash,tamTabla);
    cantidadPalabras = leerArchivo(tablaHash,nombre,tamTabla);
}