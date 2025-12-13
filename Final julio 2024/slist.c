#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (; nodo->sig != NULL; nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_buscar(SList lista, int dato) {
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (nodo->dato == dato) {
      return 1;
    }
  }

  return 0;
}

SList buscar_por_cantidad_menores(SList lista, int cantidadMenores) {
  assert(cantidadMenores >= 0);
  if(lista == NULL) {
    return NULL;
  }

  SList nuevaLista = slist_crear();
  SList nodo = lista;
  while(nodo != NULL) {
    SList aux = lista;
    int contador = 0;
    while(aux != nodo){
      if(aux->dato < nodo->dato) {
        contador++;
      }
      aux = aux->sig;
    }
    if(contador == cantidadMenores) {
      nuevaLista = slist_agregar_final(nuevaLista, nodo->dato);
    }
    nodo = nodo->sig;
  }

  return nuevaLista;
}

SList insertar_en_posicion(SList lista, int pos, int dato) {
  if(slist_buscar(lista, dato) == 1) {
    return lista;
  }

  if(lista == NULL || pos <= 0) {
    lista = slist_agregar_inicio(lista, dato);
    return lista;
  }
  SList nodo = lista;
  SList ant = NULL;
  int contador = 0;
  while(contador < pos && nodo != NULL) {
    ant = nodo;
    nodo = nodo->sig;
    contador++;
  }
  if(nodo == NULL) {
    lista = slist_agregar_final(lista, dato);
    return lista;
  }
  SList nuevoNodo = malloc(sizeof(SNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  ant->sig = nuevoNodo;
  nuevoNodo->sig = nodo;

  return lista;
}

SList eliminar_en_posicion(SList lista, int pos) {
  assert(pos >= 0);
  if(lista == NULL) {
    return NULL;
  }
  SList nodoAEliminar = lista;
  if(pos == 0) {
    lista = nodoAEliminar->sig;
    free(nodoAEliminar);
    return lista;
  }
  SList ant = NULL;
  int contador = 0;
  while(contador < pos && nodoAEliminar != NULL) {
    contador++;
    ant = nodoAEliminar;
    nodoAEliminar = nodoAEliminar->sig;
  }
  if(nodoAEliminar == NULL) {
    return lista;
  }
  ant->sig = nodoAEliminar->sig;
  free(nodoAEliminar);
  return lista;
}

int slist_longitud(SList lista) {
  int contador = 0;
  SList nodo = lista;
  while(nodo != NULL) {
    contador++;
    nodo = nodo->sig;
  }

  return contador;
}

SList ordenar_por_cantidadMenores(SList lista) {
  int longitud = slist_longitud(lista);
  if(longitud == 0) {
    return NULL;
  }

  SList nuevaLista = slist_crear();
  for(int i = 0; i < longitud; i++) {
    SList aux = buscar_por_cantidad_menores(lista, i);
    for(SList nodo = aux; nodo != NULL; nodo = nodo->sig) {
      nuevaLista = slist_agregar_final(nuevaLista, nodo->dato);
    }
    slist_destruir(aux);
  }

  return nuevaLista;
}