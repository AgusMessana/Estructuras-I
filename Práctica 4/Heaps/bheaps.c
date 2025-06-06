#include "bheaps.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy) {
  if (heap == NULL || dato == NULL || copy == NULL) {
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
  while (i > 1 && heap->comp(heap->arr[i], heap->arr[i / 2]) > 0) {
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
BHeap bheap_eliminar(BHeap heap, void *dato, FuncionDestructora dest) {
  if (heap == NULL || dato == NULL || dest == NULL) {
    return heap;
  }
  int encontrado = 0;
  for (int i = 1; i <= heap->ultimo && encontrado == 0; i++) {
    if (heap->comp(dato, heap->arr[i]) == 0) {
      void *temp = heap->arr[i];
      heap->arr[i] = heap->arr[heap->ultimo];
      heap->arr[heap->ultimo] = temp;
      dest(heap->arr[heap->ultimo]);
      heap->ultimo--;

      int limite = heap->ultimo / 2;
      while (i <= limite) {
        int hijo_izq = 2 * i;
        int hijo_der = 2 * i + 1;
        int hijo_mayor = hijo_izq;

        if (hijo_der <= heap->ultimo
            && heap->comp(heap->arr[hijo_der], heap->arr[hijo_izq]) > 0) {
          // Chequea que exista hijo derecho. Si existe, lo compara con el izquierdo.
          hijo_mayor = hijo_der;
        }

        if (heap->comp(heap->arr[hijo_mayor], heap->arr[i]) > 0) {
          void *temp = heap->arr[i];
          heap->arr[i] = heap->arr[hijo_mayor];
          heap->arr[hijo_mayor] = temp;
          i = hijo_mayor;
        } else {
          break;
        }
      }

      encontrado = 1;
    }
  }

  return heap;
}

/**
 * Crea un heap binario a partir de un arreglo arbitrario sin usar la función
 * para insertar valores nuevos.
 */
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,
                            FuncionComparadora comp) {
  if (arr == NULL || largo <= 0 || comp == NULL || copiar == NULL) {
    return NULL;
  }
  BHeap heap = bheap_crear(largo, comp);
  if (heap == NULL) {
    return NULL;
  }
  for (int i = 0; i < largo; i++) {
    heap->arr[i + 1] = copiar(arr[i]);
    if (heap->arr[i + 1] == NULL) {
      // Liberar lo copiado hasta ahora
      for (int j = 1; j <= i; j++) {
        free(heap->arr[j]);
      }
      free(heap->arr);
      free(heap);
      return NULL;
    }
  }
  heap->ultimo = largo;

  for (int i = largo / 2; i >= 1; i--) {
    int j = i;
    while (j <= heap->ultimo / 2) {
      int hijo_izq = 2 * j;
      int hijo_der = 2 * j + 1;
      int hijo_max = hijo_izq;

      if (hijo_der <= heap->ultimo
          && heap->comp(heap->arr[hijo_der], heap->arr[hijo_izq]) > 0) {
        hijo_max = hijo_der;
      }

      if (heap->comp(heap->arr[hijo_max], heap->arr[j]) > 0) {
        void *temp = heap->arr[j];
        heap->arr[j] = heap->arr[hijo_max];
        heap->arr[hijo_max] = temp;
        j = hijo_max;
      } else {
        break;
      }
    }
  }

  return heap;
}
