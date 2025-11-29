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

int slist_longitud(SList lista) {
  int contador = 0;
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    contador++;
  }
  return contador;
}

SList slist_concatenar(SList lista1, SList lista2) {
  if (lista1 == NULL) {
    return lista2;
  }

  SList nodo = lista1;
  while (nodo->sig != NULL) {   // Mientras el siguiente no sea nuelo, recorro la lista 1.
    nodo = nodo->sig;
  }

  nodo->sig = lista2;           // En el último nodo de lista 1 enlazo el primero de lista 2.
  return lista1;                // Devuelvo la lista 1 modificada.
}

SList slist_insertar(SList lista, int dato, int pos) {
  SList nuevoNodo = malloc(sizeof(SNodo));
  if (nuevoNodo == NULL) {
    return lista;
  }

  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (pos <= 0 || lista == NULL) {
    nuevoNodo->sig = lista;
    return nuevoNodo;
  }

  SList nodo = lista;
  int contador = 0;
  while (nodo->sig != NULL && contador < pos - 1) {
    nodo = nodo->sig;
    contador++;
  }

  nuevoNodo->sig = nodo->sig;
  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_eliminar(SList lista, int pos) {
  if (lista == NULL) {
    return lista;
  }

  if (pos == 0) {
    SList nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
    return lista;
  }

  SList nodo = lista;
  int contador = 0;
  while (nodo->sig != NULL && contador < pos - 1) {
    nodo = nodo->sig;
    contador++;
  }

  if (nodo->sig == NULL) {
    return lista;
  }

  SList nodoAEliminar = nodo->sig;
  nodo->sig = nodoAEliminar->sig;
  free(nodoAEliminar);
  return lista;
}

int slist_contiene(SList lista, int dato) {
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (nodo->dato == dato) {
      return 1;
    }
  }

  return 0;
}

int slist_indice(SList lista, int dato) {
  int indice = 0;

  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (nodo->dato = dato) {
      return indice;
    }
    indice++;
  }

  return -1;
}

SList slist_intersecar(SList lista1, SList lista2) {
  if (lista1 == NULL || lista2 == NULL) {
    return slist_crear();
  }

  SList nuevaLista = slist_crear();

  for (SList n1 = lista1; n1 != NULL; n1 = n1->sig) {
    if (slist_contiene(lista2, n1->dato)) {
      if (!slist_contiene(nuevaLista, n1->dato)) {
        nuevaLista = slist_agregar_final(nuevaLista, n1->dato);
      }
    }
  }

  return nuevaLista;
}

SList slist_reverso(SList lista) {
  SList nuevaLista = slist_crear();
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    nuevaLista = slist_agregar_inicio(nuevaLista, nodo->dato);
  }

  return nuevaLista;
}

SList slist_intercalar(SList lista1, SList lista2) {
  SList nuevaLista = slist_crear();
  if (lista1 == NULL) {
    for (SList n = lista2; n != NULL; n = n->sig)
      nuevaLista = slist_agregar_final(nuevaLista, n->dato);
    return nuevaLista;
  }
  if (lista2 == NULL) {
    for (SList n = lista1; n != NULL; n = n->sig)
      nuevaLista = slist_agregar_final(nuevaLista, n->dato);
    return nuevaLista;
  }

  SList nodo1 = lista1;
  SList nodo2 = lista2;

  while (nodo1 != NULL && nodo2 != NULL) {
    nuevaLista = slist_agregar_final(nuevaLista, nodo1->dato);
    nuevaLista = slist_agregar_final(nuevaLista, nodo2->dato);

    nodo1 = nodo1->sig;
    nodo2 = nodo2->sig;
  }
  while (nodo1 != NULL) {
    nuevaLista = slist_agregar_final(nuevaLista, nodo1->dato);
    nodo1 = nodo1->sig;
  }
  while (nodo2 != NULL) {
    nuevaLista = slist_agregar_final(nuevaLista, nodo2->dato);
    nodo2 = nodo2->sig;
  }

  return nuevaLista;
}

SList slist_partir(SList lista) {
  if (lista == NULL || lista->sig == NULL) {
    return slist_crear();
  }

  int longitud = slist_longitud(lista);
  int tamPrimera = (longitud + 1) / 2;
  int contador = 0;
  SList nodo = lista;

  while (contador < tamPrimera) {
    nodo = nodo->sig;
    contador++;
  }

  SList segunda = nodo->sig;
  nodo->sig = NULL;

  return segunda;
}
