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
        fscanf(archivo,"%s",palabraExtraida);
        insertarPalabra(tablaHash,palabraExtraida,tamTabla);
        totalDePalabras++;
        free(palabraExtraida);
    }
    fclose(archivo);
    tablaHash[0]->totalDePalabras = totalDePalabras;

    return totalDePalabras;

    int maximo(Nodo* tablaHash[], int tamTabla){
        int maximoDePalabras; 
        int cantidadDePalabras; //Variables para el maximo y la cantidad total de palabras que hay en la posicion
        Nodo *nodoAux;
        for(int cont=0; cont<tamTabla;i++){
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

        return maximoDePalabras;
    }

    int minimo(Nodo *tablaHash,int tamTabla){
        int minimo


    }