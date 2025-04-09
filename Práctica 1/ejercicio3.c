#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct {
int* direccion;
int capacidad;
} ArregloEnteros;

ArregloEnteros* arreglo_enteros_crear(int capacidad) {
    ArregloEnteros* arreglo = (ArregloEnteros*)malloc(sizeof(ArregloEnteros));
    arreglo -> direccion = (int*)malloc(capacidad * sizeof(int));
    arreglo -> capacidad = capacidad;

    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo) {
    free(arreglo->direccion);
    free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos) {
    if (pos < 0 || pos >= arreglo->capacidad) {
        return -1;
    }
    return(arreglo->direccion[pos]);
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato) {
    if (pos < 0 || pos >= arreglo->capacidad) {
        return -1;
    }

    arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo) {
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo) {
    for (int i = 0; i < arreglo->capacidad; i++) {
        printf("%d\n", arreglo->direccion[i]);
    }
}

