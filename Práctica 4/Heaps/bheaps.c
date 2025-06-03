#include "bheaps.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Guarda un arreglo dinámico y su capacidad, el último índice ocupado del
 * arreglo, y un puntero a una función de comparación.
 */
typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
};

/**
 * Crea un heap vacío con una capacidad y una función de comparación dadas.
 */
BHeap bheap_crear(int cap, FuncionComparadora comp) {
  if (cap == 0 || comp == NULL) {
    return NULL;
  }

  BHeap heap = malloc(sizeof(struct _BHeap));
  if (heap == NULL) {
    return NULL;
  }

  heap->arr = malloc(sizeof(void *) * (cap + 1));       // El +1 es para el índice 0, reservado como basura
  if (heap->arr == NULL) {
    free(heap);
    return NULL;
  }

  heap->capacidad = cap;
  heap->ultimo = 0;
  heap->comp = comp;

  return heap;
}

 /**
  * Destruye el heap
  */
void bheap_destruir(BHeap heap, FuncionDestructora dest) {
  if (heap == NULL) {
    return;
  }

  if (dest != NULL) {
    for (int i = 1; i <= heap->ultimo; i++) {
      dest(heap->arr[i]);
    }
  }

  free(heap->arr);
  free(heap);
}

/**
 * Retorna 1 si el heap esta vacío y 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap) {
  return (heap == NULL) || (heap->ultimo == 0);
}

/**
 * Recorra los nodos utilizando busqueda por extensión, aplicando la función
 * dada en cada elemento.
 */
void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
  if (bheap_es_vacio(heap) || visit == NULL) {
    return;
  }
  for (int i = 1; i <= heap->ultimo; i++) {
    visit(heap->arr[i]);
  }
}

/**
 * Agrega un elemento al heap, realocando el arreglo en caso de ser necesario.
 * El resultado debe ser nuevamente un heap binario.
 */
BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy,
                     FuncionComparadora comp) {
  if (heap == NULL || dato == NULL || copy == NULL || comp == NULL) {
    return heap;
  }

  if (heap->ultimo >= heap->capacidad) {
    int nueva_capacidad = heap->capacidad * 2;
    void **nuevo_arr =
        realloc(heap->arr, sizeof(void *) * (nueva_capacidad + 1));
    if (nuevo_arr == NULL) {
      return heap;
    }
    heap->arr = nuevo_arr;
    heap->capacidad = nueva_capacidad;
  }
  heap->ultimo++;
  heap->arr[heap->ultimo] = copy(dato);

  int i = heap->ultimo;
  while (i > 1 && comp(heap->arr[i], heap->arr[i / 2]) > 0) {
    void *temp = heap->arr[i / 2];
    heap->arr[i / 2] = heap->arr[i];
    heap->arr[i] = temp;
    i = i / 2;
  }

  return heap;
}

/**
 * Elimina un elemento del heap. El resultado debe ser nuevamente un heap
 * binario.
 */
BHeap bheap_eliminar(BHeap heap, void *dato, FuncionComparadora comp,
                     FuncionDestructora dest) {

}
