#include <stdio.h>
#include <stdlib.h>
#include "Ej1.h"

void *no_copia(void *dato) {
  return dato;
}

int cant_elem(BSTree arbol) {
  if (arbol == NULL) {
    return 0;
  }

  return 1 + cant_elem(arbol->izq) + cant_elem(arbol->der);
}

BHeap crear_heap(int cap) {
  BHeap heap = malloc(sizeof(struct _BHeap));
  heap->arr = malloc(sizeof(void *) * (cap + 1));
  heap->capacidad = cap;
  heap->ultimo = 0;

  return heap;
}


void llenar_arr(BSTree arbol, BHeap heap, int *indice) {
  if (arbol == NULL) {
    return;
  }
  llenar_arr(arbol->izq, heap, indice);
  heap->arr[*indice] = no_copia(arbol->dato);
  (*indice)++;
  llenar_arr(arbol->der, heap, indice);
}

void swap(void **arr, int i, int j) {
  void *temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void heapify(BHeap heap, int n, int i, FuncionComparadora comp) {
  int mas_grande = i;
  int izq = 2 * i;
  int der = 2 * i + 1;

  if (izq <= n && comp(heap->arr[izq], heap->arr[mas_grande]) > 0) {
    mas_grande = izq;
  }
  if (der <= n && comp(heap->arr[der], heap->arr[mas_grande]) > 0) {
    mas_grande = der;
  }
  if (mas_grande != i) {
    swap(heap->arr, i, mas_grande);
    heapify(heap, n, mas_grande, comp);
  }
}

void construir_heap(BHeap heap, FuncionComparadora comp) {
  int n = heap->ultimo;
  for (int i = n / 2; i >= 1; i--) {
    heapify(heap, n, i, comp);
  }
}

BHeap bst_to_heap(BSTree arbol, FuncionComparadora comp) {
  if (arbol == NULL) {
    return NULL;
  }
  int cantidad = cant_elem(arbol);
  BHeap heap = crear_heap(cantidad);
  heap->ultimo = cantidad;

  int indice = 1;
  llenar_arr(arbol, heap, &indice);
  construir_heap(heap, comp);

  return heap;
}
