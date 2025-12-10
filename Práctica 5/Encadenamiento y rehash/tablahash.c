#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct _NodoHash {
  void *dato;
  struct _NodoHash *sig;
} NodoHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  NodoHash **elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(NodoHash *) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx] = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) {
  return tabla->numElems;
}

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) {
  return tabla->capacidad;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    NodoHash *nodo = tabla->elems[idx];
    while (nodo != NULL) {
      NodoHash *sig = nodo->sig;

      tabla->destr(nodo->dato);
      free(nodo);

      nodo = sig;
    }
  }

  free(tabla->elems);
  free(tabla);
}

/**
 * Duplica la capacidad de la tabla y reposicione todos los elementos de acuerdo a la nueva posición que le asigne la función de hash.
 */
void tablahash_redimensionar(TablaHash tabla) {
  NodoHash **viejoElems = tabla->elems;
  unsigned viejaCap = tabla->capacidad;

  unsigned nuevaCap = viejaCap * 2;
  NodoHash **nuevoElems = malloc(sizeof(NodoHash *) * nuevaCap);
  assert(nuevoElems != NULL);
  for (unsigned i = 0; i < nuevaCap; ++i) {
    nuevoElems[i] = NULL;
  }
  tabla->elems = nuevoElems;
  tabla->capacidad = nuevaCap;

  for(unsigned i = 0; i < viejaCap; ++i) {
    NodoHash *nodo = viejoElems[i];
    while(nodo != NULL) {
      NodoHash *sig = nodo->sig;
      unsigned idx_nuevo = tabla->hash(nodo->dato) % tabla->capacidad;

      nodo->sig = tabla->elems[idx_nuevo];
      tabla->elems[idx_nuevo] = nodo;
      nodo = sig;
    }
  }

  free(viejoElems);
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  float limite_fdc = 0.7;
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  NodoHash *nodo = tabla->elems[idx];

  while (nodo != NULL) {
    if (tabla->comp(nodo->dato, dato) == 0) {
      tabla->destr(nodo->dato);
      nodo->dato = tabla->copia(dato);
      return;
    }
    nodo = nodo->sig;
  }

  float fdc = (float)(tabla->numElems + 1) / (float)tabla->capacidad;
  if(fdc >= limite_fdc) {
    tablahash_redimensionar(tabla);
    idx = tabla->hash(dato) % tabla->capacidad;
  }

  NodoHash *nuevoNodo = malloc(sizeof(NodoHash));
  nuevoNodo->dato = tabla->copia(dato);

  nuevoNodo->sig = tabla->elems[idx];
  tabla->elems[idx] = nuevoNodo;

  tabla->numElems++;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  NodoHash *nodo = tabla->elems[idx];

  while (nodo != NULL) {
    if (tabla->comp(nodo->dato, dato) == 0) {
      return nodo->dato;
    }
    nodo = nodo->sig;
  }

  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  NodoHash *actual = tabla->elems[idx];
  NodoHash *anterior = NULL;

  while (actual != NULL && tabla->comp(actual->dato, dato) != 0) {
    anterior = actual;
    actual = actual->sig;
  }
  if (actual != NULL) {
    if (anterior == NULL) {
      tabla->elems[idx] = actual->sig;
    } else {
      anterior->sig = actual->sig;
    }
    tabla->destr(actual->dato);
    free(actual);
    tabla->numElems--;
  }
}
