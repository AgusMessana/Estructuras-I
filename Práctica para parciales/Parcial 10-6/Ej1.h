#ifndef __EJ1_H__
#define __EJ1_H__
#include <stddef.h>

typedef struct _BSTNodo {
  void *dato;
  struct _BSTNodo *izq;
  struct _BSTNodo *der;
} BSTNodo;

typedef BSTNodo *BSTree;

typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionDestructora)(void *dato);

typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
} *BHeap;

/**
 * Dado un árbol binario de búsqueda general y una función comparadora,
 * construya un heap con los datos presentes en el árbol. El heap resultante NO
 * debe tener copias físicas de los datos.
 */
BHeap bst_to_heap (BSTree arbol, FuncionComparadora comp);

#endif
