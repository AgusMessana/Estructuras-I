#ifndef __EJERCICIOS_CHATGPT__H
#define __EJERCICIOS_CHATGPT__H

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;
typedef struct _BTNodo *BTree;

struct _BST_Nodo {
  int dato;
  struct _BST_Nodo *izq, *der;
};
typedef struct _BST_Nodo *BSTree;

typedef struct _AVL_Nodo {
  int dato;
  struct _AVL_Nodo *izq, *der;
  int altura;
} AVL_Nodo;
struct _AVL {
  AVL_Nodo *raiz;
};
typedef struct _AVL *AVL;

/**
 * Devuelve la altura de un árbol binario.
 */
int altura(BTree arbol);

/**
 * Construye el espejo de un árbol binario.
 */
BTree espejo(BTree arbol);

/**
 * Elimina un nodo de un árbol binario de búsqueda.
 */
BSTree abb_eliminar(BSTree a, int x);

/**
 * Verifica si un árbol binario cumple la propiedad de búsqueda.
 * Devuelve 1 si lo es, y 0 si no.
 */
int es_abb_aux(BTree a, int *min, int *max);
int es_abb(BTree a);

/**
 * Intercambia dos enteros usando punteros
 */
void swap_int(int *x, int *y);

/**
 * Devuelve la posición del padre en un heap.
 */
int padre(int i);

/**
 * Devuelve la posición del hijo izquierdo en un heap
 */
int izq(int i);

/**
 * Devuelve la posición del hijo derecho en un heap
 */
int der(int i);

/**
 * Hunde el elemento en la posición dada hasta que cumpla la propiedad de
 * max-heap
 */
void hundir(int pos, int *arr, int n);

/**
 * Flota el valor en la posición dada hacia arriba si es mayor que su padre
 */
void flotar(int pos, int *heap);

/**
 * Dado un arreglo desordenado de n enteros, implementá la construcción de un
 * max-heap utilizando la función hundir.
 */
int *max_heap(int *arr, int n);

/**
 * Implementar funciones insertar, extraer_max y ver_max usando un arreglo que
 * represente un max-heap.
 */
void insertar(int *heap, int *n, int valor, int len);
int ver_max(int *heap, int n);
int extraer_max(int *heap, int *n);

/**
 * Implementar bubblesort, insertionsort, quicksort y heapsort.
 */


/**
 * Implementar un algoritmo que ordene un arreglo usando un min-heap, en vez de
 * un max-heap.
 */
#endif
