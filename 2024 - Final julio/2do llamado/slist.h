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
 * Devuelve 1 si el elemento está en la lista y 0 si no.
 */
int slist_buscar(SList lista, int dato);

/**
 * Devuelve una lista con los elementos que tienen cantidadMenores igual a la
 * dada
 */
SList buscar_por_cantidad_menores(SList lista, int cantidadMenores);

/**
 * Agrega un elemento en la posición dada.
 */
SList insertar_en_posicion(SList lista, int pos, int dato);

/**
 * Borra un elemento en la posición dada.
 */
SList eliminar_en_posicion(SList lista, int pos);

/**
 * Calcula la longitud de la lista.
 */
int slist_longitud(SList lista);

/**
 * Ordena la lista de menor a mayor por cantidadMenores.
 */
SList ordenar_por_cantidadMenores(SList lista);

#endif                          /* __SLIST_H__ */
