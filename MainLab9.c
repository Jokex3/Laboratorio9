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

#ifndef Lab9_h
#include "Lab9.h"
#define Lab9_h
#endif


int main(){
    char *nombreArchivo; //Declarar string para el nombre
    nombreArchivo = (char *)malloc(sizeof(char)*50);//Pedimos tamaño suficiente
    int tamTabla;//Variable para el tamaño que tendra la tabla hash
    printf("Ingrese el nombre del archivo: ");
    scanf("%s",nombreArchivo);
    printf("\nIngrese el tama%co de la tabla hash: ",164);
    scanf("%i",&tamTabla);

    Nodo *tablaHash[tamTabla]; //Declaramos la tabla Hash donde seran las posicion
    creatablahash(tablaHash,nombreArchivo,tamTabla);
    //Para mostrar el maximo, minimo y el promedio
    printf("\nCantidad: %i",tablaHash[0]->totalDePalabras);
    int max = maximo(tablaHash,tamTabla); //Variable que obtiene maximo como el valor que da la funcion
    int min = minimo(tablaHash,tamTabla); //Variable que obtiene minimo como el valor que retorna la funcion
    int prom = promedio(tablaHash,tamTabla); //Obtiene el promedio

    printf("\nEl maximo de palabras es: %i",max); //Las imprime
    printf("\nEl minimo de palabras es: %i",min);
    printf("\nEl promedio de palabras es: %i",prom);
    crearArchivoParaMostrar(tablaHash,tamTabla);

    int opcion=0;
    do{
        printf("\n¿Desea buscar una palabra?\n1.Si\n2.No");
        double segundos;
        clock_t inicio; clock_t final;
        scanf("%i",&opcion);
        switch(opcion){
            case 1: printf("\n\nIngrese la palabra que esta buscando: ");
                    char palabra[30];
                    scanf("%s",palabra);
                    inicio = clock();
                    if(busqueda(tablaHash,palabra,tamTabla)==0){
                        final = clock();
                        printf("\nPalabra encontrada");
                        segundos = (double)(final-inicio)/CLOCKS_PER_SEC;
                        printf("\nTiempo de busqueda: %f",segundos);
                    }else{
                        printf("\nPalabra no encontrada");  
                    }
                    break;
        }
    }while(opcion !=2);

    liberarMemoria(tablaHash,tamTabla);
    free(nombreArchivo);

    return 0;
}