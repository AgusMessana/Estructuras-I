#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparadora) (int dato1, int dato2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

// Devuelve la longitud de una lista
int slist_longitud (SList lista);

// Toma dos listas y concatena la segunda a la primera
void slist_concatenar(SList* lista1, SList lista2);

// Inserta un dato en una posición arbitraria
void slist_insertar(SList* lista, int dato, int pos);

// Borra de la lista un dato apuntado en una posición arbitraria
void slist_eliminar(SList* lista, int pos);

// Determina si un elemento está en una lista dada
// Devuelve 0 si el elemento no está y 1 si el elemento está
int slist_contiene(SList lista, int dato);

// Devuelve la posición de la primera ocurrencia de un elemento si el mismo está en la lista dada, y -1 en caso que no esté.
int slist_indice(SList lista, int dato);

// Devuelve una nueva lista con los elementos comunes de dos listas dadas por parametro.
SList slist_intersecar(SList lista1, SList lista2);

// Trabaja igual que la función anterior, pero con una función comparadora.
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadora comp);

// Ordena una lista de acuerdo al criterio dado por una funcion de comparacion pasada por parametro.
SList slist_ordenar(SList lista, FuncionComparadora comp);

// Obtiene el reverso de una lista
SList reverso(SList lista);

// Dadas dos listas, intercale sus elementos en la lista resultante.
SList slist_intercalar(SList lista1, SList lista2);

// Divide una lista a la mitad. En caso de longitud impar, la primera lista tendrá longitud n+1 y la segunda n. Retorna un puntero al primer elemento de la segunda mitad, siempre que sea no vaca.
SList slist_partir(SList lista);

#endif /* __SLIST_H__ */