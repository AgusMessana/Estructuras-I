#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conjunto.h>

/**
 * Dado un conjunto, devuelve 1 si el elemento está en él y 0 si no.
 */
int pertenece(SList conjunto, int dato) {
  for (SList nodo = conjunto; nodo != NULL; nodo = nodo->sig) {
    if (nodo->dato == dato) {
      return 1;
    }
  }

  return 0;
}

/**
 * Dado un conjunto, inserta un elemento en el él. Si ya estaba, no lo inserta.
 */
SList insertar(SList conjunto, int dato) {
  if (pertenece(conjunto, dato) == 0) {
    SNodo *nuevoNodo = malloc(sizeof(SNodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = dato;
    nuevoNodo->sig = conjunto;
    return nuevoNodo;
  }

  return conjunto;
}

/**
 * Devuelve 1 si el candidato es el neutro de la operación y 0 si no.
 */
static int es_neutro(int candidato, int valor, Operacion op) {
  if (op(candidato, valor) == valor && op(valor, candidato) == valor) {
    return 1;
  }

  return 0;
}

/**
 * Devuelve 1 si el candidato es el inverso de la operación y 0 si no.
 */
static int es_inverso(int candidato, int valor, int neutro, Operacion op) {
  if (op(candidato, valor) == neutro && op(valor, candidato) == neutro) {
    return 1;
  }

  return 0;
}

/**
 * Dado un conjunto, un elemento de dicho conjunto que es candidato a elemento neutro y una operación de enteros, devuelve 1 si el conjunto dotado de la operación es un grupo y 0 si no
 */
int es_grupo(SList conjunto, int neutro, Operacion op) {
  assert(op != NULL);
  if (conjunto == NULL || pertenece(conjunto, neutro) == 0) {
    return 0;
  }

  for (SList nodo = conjunto; nodo != NULL; nodo = nodo->sig) {
    if (es_neutro(neutro, nodo->dato, op) == 0) {
      return 0;
    }
  }

  for (SList nodo1 = conjunto; nodo1 != NULL; nodo1 = nodo1->sig) {
    int hay_inverso = 0;
    int val_act = nodo1->dato;
    for (SList nodo2 = conjunto; nodo2 != NULL && hay_inverso != 1;
         nodo2 = nodo2->sig) {
      if (es_inverso(nodo2->dato, val_act, neutro, op) == 1) {
        hay_inverso = 1;
      }
    }

    if (hay_inverso == 0) {
      return 0;
    }
  }

  return 1;
}
