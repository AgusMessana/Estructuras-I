#ifndef __SDLIST_H__
#define __SDLIST_H__

#include <stddef.h>

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef struct SList {
  SNodo *primero;
  SNodo *ultimo;
} SList;

/**
 * Devuelve una lista inicializada vacía.
 */
SList sdlist_crear();

/**
 * Agrega un elemento al inicio de la lista.
 */
SList sdlist_agregar_inicio(SList lista, int dato);

/**
 * Agrega un elemento al final de la lista.
 */
SList sdlist_agregar_final(SList lista, int dato);

#endif                          /* __SDLIST_H__ */
