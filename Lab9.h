#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Tnodo{
    char *palabra;
    int totalDePalabras;
    struct Tnodo *sgte;
}Nodo;

Nodo *crearNodo(char *palabra){
    int largo = strlen(palabra); //Strlen permite obtener el largo de un string sin contar \0, ej: hola, su largo seria 4
    Nodo *nodoAux = malloc(sizeof(struct Tnodo));
    nodoAux->sgte = NULL;
    nodoAux->palabra = malloc(sizeof(char)*(largo+1)); //Pedir memoria de tipo char para poder hacer un arreglo con el largo+1 para \0
    strcpy(nodoAux->palabra,palabra); //Copia el string de palabra y la guarda en el string de la estructura

    return nodoAux; //retornamos el nodo
}

//Funcion para agregar el nodo a la tabla y a la lista
void insertarPalabra(Nodo *TablaHash[],char *palabra,int tamTabla){ 
    //Recordar que palabra es la palabra extraida del archivo
    int resultadoHash;
    Nodo *nodoAux1; Nodo *nodoAux2;
    resultadoHash = operacionHash(palabra,tamTabla); //resultadoHash resibe la clave (posicion) donde se guardara
    nodoAux1 = TablaHash[resultadoHash]; //nodoAux1 guarda el puntero a la tabla
    nodoAux2 = crearNodo(palabra); //se crea el nodoAux2 con la nueva palabra
    TablaHash[resultadoHash] = nodoAux2; //la tabla apunta al nodo nuevo
    TablaHash[resultadoHash]->sgte = nodoAux1; //
}


//Funcion que retorna la cantidad total de palabras procesadas
int *leerArchivo(Nodo* tablaHash[],char *nombre, int tamTabla){
    strcat(nombre,".txt"); //Agrega .txt despues del ultimo caracter del string
    char *palabraExtraida;
    int totalDePalabras = 0;
    FILE *archivo = fopen(nombre,"r");
    while(!feof(archivo)){ //Mientras no sea final de archivo
        palabraExtraida = malloc(sizeof(char)*30);
        fscanf(archivo,"%s",palabraExtraida);
        insertarPalabra(tablaHash,palabraExtraida,tamTabla);
        totalDePalabras++;
        free(palabraExtraida);
    }
    fclose(archivo);
    tablaHash[0]->totalDePalabras = totalDePalabras;

    return totalDePalabras;
}