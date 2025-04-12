#ifndef __cdlist1_H__
#define __cdlist1_H__

#include <stddef.h>

typedef struct _CDNodo {
    int dato;
    struct _CDNodo* sig;
    struct _CDNodo* ant;
} CDNodo;

typedef void (*FuncionVisitante) (int dato);

typedef enum {
    CDLIST_RECORRIDO_HACIA_ADELANTE,
    CDLIST_RECORRIDO_HACIA_ATRAS
} CDListOrdenDeRecorrido;

typedef struct _cdlist {
    CDNodo* ultimo;
} CDList;

// Devuelve una lista vacía
CDList cdlist_crear();

// Destruye una lista
void cdlist_destruir(CDList* cdlista);

// Determina si la lista es vacía.
int cdlist_vacia(CDList cdlista);

// Recorrido de la lista, utilizando la funcion pasada.
void cdlist_recorrer(CDList cdlista, CDListOrdenDeRecorrido orden, FuncionVisitante visit);

// Agrega un elemento al final de la lista
CDList cdlist_agregar_final(CDList cdlista, int dato);

// Agrega un elemento al inicio de la lista
CDList cdlist_agregar_inicio(CDList cdlista, int dato);

// Devuelve la longitud de una lista
int cdlist_longitud (CDList cdlista);

// Toma dos listas y concatena la segunda a la primera
void cdlist_concatenar(CDList* cdlista1, CDList cdlista2);

// Inserta un dato en una posición arbitraria
void cdlist_insertar(CDList* cdlista, int dato, int pos);

// Borra de una lista un dato apuntado en una posicion arbitraria
void cdlist_eliminar (CDList* cdlista, int pos);

// Determina si un elemento está en una lista dada
// Devuelve 0 si el elemento no está y 1 si el elemento está
int cdlist_contiene(CDList cdlista, int dato);

// Devuelve la posición de la primera ocurrencia de un elemento si el mismo está en la lista dada, y -1 en caso que no esté.
int cdlist_indice(CDList cdlista, int dato);

// Devuelve una nueva lista con los elementos comunes de dos listas dadas por parametro.
CDList cdlist_intersecar(CDList cdlista1, CDList cdlista2);

// Obtiene el reverso de una lista
CDList reverso(CDList cdlista);

#endif