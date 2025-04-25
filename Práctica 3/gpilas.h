#ifndef __GPILAS_H__
#define __GPILAS_H__
#include <Estructuras-I/Práctica 2/GList/glist.h>

#include <stddef.h>

typedef GList Pila;

// Crea e inicializa una nueva pila vaca con la capacidad dada
Pila gpila_crear();

// Libera la memoria requerida para la pila
void gpila_destruir(Pila pila, FuncionDestructora destroy);

// Retorna 1 si la pila esta vacía, y 0 en caso contrario
int gpila_es_vacia(Pila pila);

// Retorna el elemento que se encuentre en el tope de la pila, pero sin eliminarlo.
void *gpila_tope(Pila pila);

// Inserta un elemento en el tope de la pila
Pila gpila_apilar(Pila pila, void *elemento, FuncionCopia copy);

// Elimina el elemento que se encuentra en el tope de la pila
Pila gpila_desapilar(Pila pila);

// Imprime en orden los elementos de la pila
void gpila_imprimir(Pila pila, FuncionVisitante visit);

// Invierte el orden de una lista simplemente enlazada
GList invertir_orden(GList lista, FuncionCopia copy,
                     FuncionDestructora destroy);

#endif
