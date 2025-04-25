#include <stdio.h>
#include <stdlib.h>
#include "arregloenteros.h"
#include "pilas.h"

Pila pila_crear(int longitud) {
  ArregloEnteros *nuevoArreglo = arreglo_enteros_crear(longitud);
  if (nuevoArreglo == NULL) {
    return NULL;
  }

  Pila nuevaPila = malloc(sizeof(struct _Pila));
  if (nuevaPila == NULL) {
    return NULL;
  }

  nuevaPila->arr = nuevoArreglo;
  nuevaPila->ultimo = -1;

  return nuevaPila;
}

void pila_destruir(Pila pila) {
  if (pila != NULL) {
    arreglo_enteros_destruir(pila->arr);
    free(pila);
  }
}

int pila_es_vacia(Pila pila) {
  if (pila == NULL) {
    return 1;
  }
  return pila->ultimo == -1;
}

int pila_tope(Pila pila) {
  if (pila == NULL || pila->ultimo == -1) {
    fprintf(stderr, "Error: pila vacía\n");
    exit(EXIT_FAILURE);
  }
  return pila->arr->datos[pila->ultimo];
}

void pila_apilar(Pila pila, int elemento) {
  if (pila->ultimo == pila->arr->capacidad - 1) {
    arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad * 2);
  }

  pila->ultimo++;
  pila->arr->datos[pila->ultimo] = elemento;
}

void pila_desapilar(Pila pila) {
  if (pila == NULL || pila->ultimo == -1) {
    return;
  }
  pila->ultimo - 1;
}

void pila_imprimir(Pila pila) {
  if (pila == NULL || pila->ultimo == -1) {
    return;
  }
  for (int i = 0; i <= pila->ultimo; i++) {
    printf("%d\n", pila->arr->datos[i]);
  }
}