#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>

typedef struct _DNodo {
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo; 

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef void (*FuncionVisitante) (int dato);

typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

// Devuelve una lista vacía
DList dlist_crear();

// Destruye una lista
void dlist_destruir(DList* dlista);

// Recorrido de la lista, utilizando la funcion pasada.
void dlist_recorrer(DList dlista, DListOrdenDeRecorrido orden, FuncionVisitante visit);

// Agrega un elemento al final de la lista
DList dlist_agregar_final(DList dlista, int dato);

// Agrega un elemento al inicio de la lista
DList dlist_agregar_inicio(DList dlista, int dato);

// Borra de una lista un dato apuntado en una posicion arbitraria
void dlist_eliminar (DList* dlista, int pos);

#endif /* __DLIST_H__ */