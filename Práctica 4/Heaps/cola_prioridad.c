#include "cola_prioridad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Retorna 1 si la cola esta vacía y 0 en caso contrario.
 */
int cola_de_prioridad_es_vacia(ColaPrioridad cola) {
  if (cola == NULL || cola->heap == NULL) {
    return 1;
  }
  return bheap_es_vacio(cola->heap);
}

/**
 * Retorna el elemento prioritario de la cola.
 */
void *cola_prioridad_maximo(ColaPrioridad cola) {
  if (cola_de_prioridad_es_vacia(cola)) {
    return NULL;
  }
  return cola->heap->arr[1];
}

/**
 * Elimina el elemento prioritario de la cola.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola, FuncionDestructora dest) {
  if (cola_de_prioridad_es_vacia(cola))
    return;

  dest(cola->heap->arr[1]);     // Liberar el dato si 'dest' no es NULL
  cola->heap->arr[1] = cola->heap->arr[cola->heap->ultimo];
  cola->heap->ultimo--;

  int i = 1;
  while (i <= cola->heap->ultimo / 2) {
    int hijo_izq = 2 * i;
    int hijo_der = 2 * i + 1;
    int hijo_mayor = hijo_izq;
    if (hijo_der <= cola->heap->ultimo &&
        cola->heap->comp(cola->heap->arr[hijo_der],
                         cola->heap->arr[hijo_izq]) > 0) {
      hijo_mayor = hijo_der;
    }
    if (cola->heap->comp(cola->heap->arr[hijo_mayor], cola->heap->arr[i]) > 0) {
      void *temp = cola->heap->arr[i];
      cola->heap->arr[i] = cola->heap->arr[hijo_mayor];
      cola->heap->arr[hijo_mayor] = temp;
      i = hijo_mayor;
    } else
      break;
  }
}

/**
 * Inserta un elemento en la cola con una determinada prioridad.
 */
void cola_prioridad_insertar(ColaPrioridad cola, void *dato,
                             FuncionCopiadora copiar) {
  bheap_insertar(cola->heap, dato, copiar);     // Reutilizas tu función existente
}
