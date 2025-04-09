#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista -> sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo -> dato = dato;
  nuevoNodo -> sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo -> sig != NULL;nodo = nodo -> sig);

  nodo -> sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo -> dato = dato;
  nuevoNodo -> sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo -> sig)
    visit(nodo->dato);
}

int slist_longitud (SList lista) {
  int cont = 0;

  for(SNodo* temp = lista; temp != NULL; temp = temp -> sig){
    cont++;
  }
  return cont;
}

void slist_concatenar(SList* lista1, SList lista2) {
  if(*lista1 == NULL){
    *lista1 = lista2;
    return;
  }

  SNodo* temp = *lista1;
  for(; temp -> sig != NULL; temp = temp -> sig);
  temp -> sig = lista2;
}

void slist_insertar(SList* lista, int dato, int pos) {
  SNodo* nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo -> dato = dato;
  if(*lista == NULL || pos == 0){
    nuevoNodo -> sig = *lista;
    *lista = nuevoNodo;
    return;
  }

  SNodo* temp = *lista; 
  for(int cont = 0; temp != NULL && cont < pos - 1; cont++){
    temp = temp -> sig;
  }

  if(temp == NULL){
    free(nuevoNodo);
    return;
  }

  nuevoNodo -> sig = temp -> sig;
  temp -> sig = nuevoNodo;
}