#ifndef __SLIST1_H__
#define __SLIST1_H__

#include <stddef.h>

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

// Ahora hay punteros al primer y último elemento de la lista
typedef struct SList {
  SNodo *primero;
  SNodo *ultimo;
} SList;

// Devuelve una lista vacía
SList slist_crear();

// Destrucción de la lista
void slist_destruir(SList * lista);

// Agrega un elemento al final de la lista
SList slist_agregar_final(SList lista, int dato);

// Agrega un elemento al inicio de la lista
SList slist_agregar_inicio(SList lista, int dato);

#endif                          /* __SLIST1_H__ */
