#ifndef __PILAS_H__
#define __PILAS_H__
#include "arregloenteros.h"

#include <stddef.h>

struct _Pila {
  ArregloEnteros *arr;
  int ultimo;                   //última posición ocupada por el arreglo
};

typedef struct _Pila *Pila;

// Crea e inicializa una nueva pila vaca con la capacidad dada
Pila pila_crear(int capacidad);

// Libera la memoria requerida para la pila
void pila_destruir(Pila pila);

// Retorna 1 si la pila esta vacía, y 0 en caso contrario
int pila_es_vacia(Pila pila);

// Retorna el elemento que se encuentre en el tope de la pila, pero sin eliminarlo.
int pila_tope(Pila pila);

// Inserta un elemento en el tope de la pila
// En caso que la pila se encuentre llena, deberá aumentar al doble la capacidad del arreglo
void pila_apilar(Pila pila, int elemento);

// Elimina el elemento que se encuentra en el tope de la pila
void pila_desapilar(Pila pila);

// Imprime en orden los elementos de la pila
void pila_imprimir(Pila pila);

#endif