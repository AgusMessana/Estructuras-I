#ifndef __HEAP_H__
#define __HEAP_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
} *BHeap;

typedef struct {
  BHeap heap;
} *ColaPrioridad;

/**
 * Crea un heap vacío con una capacidad y una función de comparación dadas.
 */
BHeap bheap_crear(int capacidad, FuncionComparadora comp);

/**
 * Destruye el heap.
 */
void bheap_destruir(BHeap heap, FuncionDestructora dest);

/**
 * Retorna 1 si el heap está vacío y 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap);

/**
 * Recorre los nodos utilizando búsqueda por extensión.
 */
void bheap_recorrer(BHeap heap, FuncionVisitante visit);

/**
 * Agrega un elemento al heap, realocando el arreglo en caso de ser necesario.
 * El resultado debe ser nuevamente un heap binario.
 */
BHeap bheap_insertar(BHeap heap, void *dato);

/**
 * Elimina un elemento del heap. El resultado debe ser nuevamente un heap
 * binario.
 */
BHeap bheap_eliminar(BHeap heap, void *dato);

/**
 * Crea un heap binario a partir de un arreglo arbirario.
 */
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,
                            FuncionComparadora comp);

/**
 * Retorna 1 si la cola está vacía y 0 en caso contrario.
 */
int cola_prioridad_es_vacia(ColaPrioridad cola);

/**
 * Retorna el elemento prioritario de la cola.
 */
void *cola_prioridad_maximo(ColaPrioridad cola);

/**
 * Elimina el elemento prioritario de la cola.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola, FuncionDestructora d);

/**
 * Inserta un elemento en la cola con una determinada prioridad.
 */
void cola_prioridad_insertar(ColaPrioridad cola, int prioridad, void *dato);

#endif
