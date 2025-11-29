#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante)(int dato);
typedef void (*FuncionComparadora)(int dato1, int dato2);

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

/**
 * Devuelve la longitud de una lista.
 */
int slist_longitud(SList lista);

/**
 * Devuelve la concatenacion de dos listas, modificando la primera.
 */
SList slist_concatenar(SList lista1, SList lista2);

/**
 * Inserta un dato en una lista en una posicion arbitraria.
 */
SList slist_insertar(SList lista, int dato, int pos);

/**
 * Borra de una lista un dato apuntado en una posicion arbitraria.
 */
SList slist_eliminar(SList lista, int pos);

/**
 * Determina si un elemento esta en una lista dada.
 */
int slist_contiene(SList lista, int dato);

/**
 * Devuelve la posicion de la primera ocurrencia de un elemento si el mismo esta en la lista dada, y -1 en caso que no este.
 */
int slist_indice(SList lista, int dato);

/**
 * Devuelve una nueva lista con los elementos comunes (independientemente de la posicion) de dos listas dadas por parametro. Las listas originales no se modifican.
 */
SList slist_intersecar(SList lista1, SList lista2);

/**
 * Trabaja como la anterior pero recibe un parametro extra que es un puntero a una funcion de comparacion que permite de nir la nocion de igualdad a ser usada al comparar elementos por igualdad.
 */
SList slist_intersecar_custom(SList lista1, SList lista2,
                              FuncionComparadora comp);

/**
 * Ordena una lista de acuerdo al criterio dado por una funcion de comparacion (que usa los mismos valores de retorno que strcmp()) pasada por parametro.
 */
SList slist_ordenar(SList lista, FuncionComparadora comp);

/**
 * Obtiene el reverso de una lista.
 */
SList slist_reverso(SList lista);

/**
 * Dadas dos listas, intercala sus elementos en la lista resultante. Por ejemplo, dadas las listas [1, 2, 3, 4] y [5, 6], debe obtener la lista [1, 5, 2, 6, 3, 4].
 */
SList slist_intercalar(SList lista1, SList lista2);

/**
 * Divide una lista a la mitad. En caso de longitud impar (2n + 1), la primer lista tendra longitud n+1 y la segunda n. Retorna un puntero al primer elemento de la segunda mitad, siempre que sea no vacía.
 */
SList slist_partir(SList lista);

#endif                          /* __SLIST_H__ */
