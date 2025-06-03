#ifndef __BHEAPS_H__
#define __BHEAPS_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _BHeap *BHeap;

/**
 * Crea un heap vacío con una capacidad y una función de comparación dadas.
 */
BHeap bheap_crear(int cap, FuncionComparadora comp);

 /**
  * Destruye el heap
  */
void bheap_destruir(BHeap heap, FuncionDestructora dest);

/**
 * Retorna 1 si el heap esta vacío y 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap);

/**
 * Recorra los nodos utilizando busqueda por extensión, aplicando la función
 * dada en cada elemento.
 */
void bheap_recorrer(BHeap heap, FuncionVisitante visit);

/**
 * Agrega un elemento al heap, realocando el arreglo en caso de ser necesario.
 * El resultado debe ser nuevamente un heap binario.
 */
BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy,
                     FuncionComparadora comp);

/**
 * Elimina un elemento del heap. El resultado debe ser nuevamente un heap
 * binario.
 */
BHeap bheap_eliminar(BHeap heap, void *dato, FuncionComparadora comp,
                     FuncionDestructora dest);

#endif
