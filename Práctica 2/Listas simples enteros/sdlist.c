#include "sdlist.h"
#include <stdlib.h>

SList sdlist_crear() {
  SList lista;
  lista.primero = NULL;
  lista.ultimo = NULL;

  return lista;
}

SList sdlist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista.primero == NULL) {
    lista.primero = nuevoNodo;
    lista.ultimo = nuevoNodo;
  } else {
    nuevoNodo->sig = lista.primero;
    lista.primero = nuevoNodo;
  }

  return lista;
}

SList sdlist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if(lista.primero == NULL) {
    lista.primero = nuevoNodo;
    lista.ultimo = nuevoNodo;
  } else {
    lista.ultimo->sig = nuevoNodo;
    lista.ultimo = nuevoNodo;
  }

  return lista;
}