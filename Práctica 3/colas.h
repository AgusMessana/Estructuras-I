#ifndef __COLAS_H__
#define __COLAS_H__

#include <stddef.h>
#include "Estructuras-I/Práctica 2/GList/glist.h"

typedef struct _Cola {
  GNode *primero;
  GNode *ultimo;
} Cola;

// Crea una cola vacía
Cola *cola_crear();

// Destruye una cola existente
void cola_destruir(Cola * cola, FuncionDestructora destroy);

// Devuelve 1 si la cola está vacía y 0 si no lo está
int cola_es_vacia(Cola cola);

// Retorna el elemento que está al inicio de la cola
void *cola_inicio(Cola cola);

// Agrega un elemento al final de la cola
Cola *cola_encolar(Cola * cola, void *elemento, FuncionCopia copy);

// Elimina el primer elemento de la cola
Cola *cola_desencolar(Cola * cola, FuncionDestructora destroy);

// Imprime los elementos de la cola
void cola_imprimir(Cola * cola, FuncionVisitante visit);

#endif
