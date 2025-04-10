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

void slist_eliminar(SList* lista, int pos){
  if(*lista == NULL){
    return;
  }

  if(pos == 0){
    SNodo* nodoAeliminar = *lista;
    *lista = (*lista)->sig;
    free(nodoAeliminar);
    return;
  }

  int cont;
  SList* temp = lista;
  for(cont = 0; cont != pos-1 && (*temp)->sig; cont++, temp = &(*temp) -> sig);

  if(*temp == NULL || (*temp) -> sig == NULL){
    return;
  }

  SNodo* nodoAeliminar = (*temp) -> sig;
  (*temp)->sig = nodoAeliminar->sig;
  free(nodoAeliminar);
  return;
}

int slist_contiene(SList lista, int dato){
  if(lista == NULL){
    return 0;
  }

  SNodo* temp = lista;
  for(;temp->dato != dato && temp->sig != NULL; temp = temp->sig);
  if(temp->sig == NULL && temp -> dato != dato){
    return 0;
  }
  return 1;
}

int slist_indice(SList lista, int dato){
  if(lista == NULL){
    return -1;
  }

  int indice = 0;
  SNodo* temp = lista;
  while(temp != NULL){
    if(temp->dato == dato){
      return indice;
    }
    indice ++;
    temp = temp->sig;
  }
  return -1;
}

