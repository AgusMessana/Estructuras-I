#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * Crea un heap vacío con una capacidad y una función de comparación dadas.
 */
BHeap bheap_crear(int capacidad, FuncionComparadora comp) {
  BHeap heap = malloc(sizeof(struct _BHeap));
  heap->arr = malloc(sizeof(void *) * (capacidad + 1));
  heap->capacidad = capacidad;
  heap->ultimo = 0;
  heap->comp = comp;

  return heap;
}

/**
 * Destruye el heap.
 */
void bheap_destruir(BHeap heap, FuncionDestructora dest) {
  if (heap == NULL) {
    return;
  }

  for (int i = 1; i <= heap->ultimo; i++) {
    dest(heap->arr[i]);
  }
  free(heap->arr);
  free(heap);
}

/**
 * Retorna 1 si el heap está vacío y 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap) {
  if (heap == NULL || heap->ultimo == 0) {
    return 1;
  }

  return 0;
}

/**
 * Recorre los nodos utilizando búsqueda por extensión.
 */
void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
  if (bheap_es_vacio(heap)) {
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
void swap(void **arr, int i, int j) {
  void *temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void sift_up(BHeap heap, int i) {
  while (i > 1 && heap->comp(heap->arr[i], heap->arr[i / 2]) > 0) {
    swap(heap->arr, i, i / 2);
    i = i / 2;
  }
}

BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy) {
  if (bheap_es_vacio(heap)) {
    return heap;
  }
  if (heap->ultimo >= heap->capacidad) {
    int nuevaCapacidad = heap->capacidad * 2;
    void **nuevoArr = realloc(heap->arr, sizeof(void *) * (nuevaCapacidad + 1));
    heap->arr = nuevoArr;
    heap->capacidad = nuevaCapacidad;
  }
  heap->ultimo++;
  heap->arr[heap->ultimo] = copy(dato);

  sift_up(heap, heap->ultimo);

  return heap;
}

/**
 * Elimina un elemento del heap. El resultado debe ser nuevamente un heap
 * binario.
 */
void heapify(BHeap heap, int cantidad, int indice) {
  int mayor = indice;
  int izq = 2 * indice;
  int der = 2 * indice + 1;
  if (izq <= cantidad && heap->comp(heap->arr[izq], heap->arr[mayor]) > 0) {
    mayor = izq;
  }
  if (der <= cantidad && heap->comp(heap->arr[der], heap->arr[mayor]) > 0) {
    mayor = der;
  }
  if (mayor != indice) {
    swap(heap->arr, indice, mayor);
    heapify(heap, cantidad, mayor);
  }
}

BHeap bheap_eliminar(BHeap heap, void *dato, FuncionDestructora dest) {
  if (bheap_es_vacio(heap)) {
    return heap;
  }

  int pos = -1;
  for (int i = 1; i <= heap->ultimo; i++) {
    if (heap->comp(heap->arr[i], dato) == 0) {
      pos = i;
      break;
    }
  }

  if (pos == -1) {
    return heap;
  }                             // Elemento no encontrado

  heap->arr[pos] = heap->arr[heap->ultimo];
  heap->ultimo--;

  // Reordenar el heap
  if (pos <= heap->ultimo) {
    // Primero intentar sift_up
    int padre = pos / 2;
    if (pos > 1 && heap->comp(heap->arr[pos], heap->arr[padre]) > 0) {
      sift_up(heap, pos);
    } else {
      // Si no necesita sift_up, hacer heapify
      heapify(heap, heap->ultimo, pos);
    }
  }

  return heap;
}

/**
 * Crea un heap binario a partir de un arreglo arbirario.
 */
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,
                            FuncionComparadora comp) {
  BHeap nuevoHeap = bheap_crear(largo, comp);
  for (int i = 0; i < largo; i++) {
    nuevoHeap->arr[i + 1] = copiar(arr[i]);
  }
  nuevoHeap->ultimo = largo;
  for (int i = largo / 2; i >= 1; i++) {
    heapify(nuevoHeap->arr, largo, 1);
  }

  return nuevoHeap;
}

/**
 * Retorna 1 si la cola está vacía y 0 en caso contrario.
 */
int cola_prioridad_es_vacia(ColaPrioridad cola) {
  if (cola == NULL) {
    return 1;
  }

  return bheap_es_vacio(cola->heap);
}

/**
 * Retorna el elemento prioritario de la cola.
 */
void *cola_prioridad_maximo(ColaPrioridad cola) {
  if (cola_prioridad_es_vacia(cola)) {
    return NULL;
  }
  return cola->heap->arr[1];
}

/**
 * Elimina el elemento prioritario de la cola.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola, FuncionDestructora d) {
  if (cola_prioridad_es_vacia(cola)) {
    return;
  }
  d(cola->heap->arr[1]);
  cola->heap->arr[1] = cola->heap->arr[cola->heap->ultimo];
  cola->heap->ultimo--;

  if (cola->heap->ultimo > 0) {
    heapify(cola->heap, cola->heap->ultimo, 1);
  }
}

/**
 * Inserta un elemento en la cola con una determinada prioridad.
 */
void cola_prioridad_insertar(ColaPrioridad cola, void *dato,
                             FuncionCopiadora copy) {
  bheap_insertar(cola->heap, dato, copy);
}
