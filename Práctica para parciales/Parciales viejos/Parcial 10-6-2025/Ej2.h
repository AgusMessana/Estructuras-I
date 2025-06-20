#ifndef __EJ2_H__
#define __EJ2_H__
#include <stddef.h>

typedef struct _AVL_Nodo {
  void *dato;
  struct _AVL_Nodo *izq, *der;
  int altura;
} AVL_Nodo;

typedef struct _AVL_Nodo *AVL;

/**
 * Dado un arreglo ORDENADO de datos y un entero n que indica el largo del
 * arreglo, construya un árbol AVL que contenga los datos del arreglo (sin
 * hacer copias físicas). No puede usarse la función insertar para árboles AVL.
 */
AVL sorted_arr_to_avl(void **arr, int n);

#endif
