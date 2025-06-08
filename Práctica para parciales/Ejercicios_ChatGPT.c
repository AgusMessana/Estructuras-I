#include <stdio.h>
#include <stdlib.h>
#include "Ejercicios_ChatGPT.h"

/**
 * Devuelve la altura de un árbol binario.
 */
int altura(BTree arbol) {
  if (arbol == NULL) {
    return -1;
  }

  int alt_izq = altura(arbol->left);
  int alt_der = altura(arbol->right);

  return 1 + (alt_izq > alt_der ? alt_izq : alt_der);
}

/**
 * Construye el espejo de un árbol binario.
 */
BTree espejo(BTree arbol) {
  if (arbol == NULL) {
    return NULL;
  }

  BTree nuevoNodo = malloc(sizeof(BTNodo));
  nuevoNodo->dato = arbol->dato;
  nuevoNodo->left = espejo(arbol->right);
  nuevoNodo->right = espejo(arbol->left);

  return nuevoNodo;
}

/**
 * Elimina un nodo de un árbol binario de búsqueda.
 */
BSTree abb_eliminar(BSTree a, int x) {
  if (a == NULL) {
    return NULL;
  }
  if (x < a->dato) {
    a->izq = abb_eliminar(a->izq, x);
  } else if (x > a->dato) {
    a->der = abb_eliminar(a->der, x);
  } else {
    if (a->izq == NULL) {
      BSTree temp = a->der;
      free(a);
      return temp;
    } else if (a->der == NULL) {
      BSTree temp = a->izq;
      free(a);
      return temp;
    } else {
      BSTree sucesor = a->der;
      while (sucesor->izq != NULL) {
        sucesor = sucesor->izq;
      }
      a->dato = sucesor->dato;
      a->der = abb_eliminar(a->der, sucesor->dato);
      return a;
    }
  }

  return a;
}

/**
 * Verifica si un árbol binario cumple la propiedad de búsqueda.
 * Devuelve 1 si lo es, y 0 si no.
 */
int es_abb_aux(BTree a, int *min, int *max) {
  if (a == NULL) {
    return 1;
  }
  if ((min != NULL && a->dato <= *min) || (max != NULL && a->dato >= *max)) {
    return 0;
  }
  return es_abb_aux(a->left, min, &(a->dato))
      && es_abb_aux(a->right, &(a->dato), max);
}

int es_abb(BTree a) {
  return es_abb_aux(a, NULL, NULL);
}

/**
 * Intercambia dos enteros usando punteros.
 */
void swap_int(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

/**
 * Devuelve la posición del padre en un heap.
 */

int padre(int i) {
  return i / 2;
}

/**
 * Devuelve la posición del hijo izquierdo en un heap.
 */
int izq(int i) {
  return 2 * i;
}

/**
 * Devuelve la posición del hijo derecho en un heap.
 */
int der(int i) {
  return 2 * i + 1;
}

/**
 * Hunde el elemento en la posición dada hasta que cumpla la propiedad de
 * max-heap.
 */
void hundir(int pos, int *arr, int n) {
  int max_pos = pos;

  int i_izq = izq(pos);
  int i_der = der(pos);

  if (i_izq < n && arr[i_izq] > arr[max_pos]) {
    max_pos = i_izq;
  }

  if (i_der < n && arr[i_der] > arr[max_pos]) {
    max_pos = i_der;
  }

  if (max_pos != pos) {
    swap_int(&arr[pos], &arr[max_pos]);
    hundir(max_pos, arr, n);
  }
}

/**
 * Flota el valor en la posición dada hacia arriba si es mayor que su padre
 */
void flotar(int pos, int *heap) {
  while (pos > 1 && heap[padre(pos)] < heap[pos]) {
    swap_int(&heap[pos], &heap[padre(pos)]);
    pos = padre(pos);
  }
}

/**
 * Dado un arreglo desordenado de n enteros, implementá la construcción de un
 * max-heap utilizando la función hundir.
 */
int *max_heap(int *arr, int n) {
  for (int i = n / 2; i >= 1; i--) {
    hundir(i, arr, n);
  }

  return arr;
}

/**
 * Implementar funciones insertar, extraer_max y ver_max usando un arreglo que
 * represente un max-heap.
 */
void insertar(int *heap, int *n, int valor, int len) {
  if (*n + 1 >= len) {
    printf("Error: heap lleno\n");
    return;
  }
  (*n)++;
  heap[*n] = valor;
  flotar(*n, heap);
}

int ver_max(int *heap, int n) {
  if (n == 0) {
    printf("Error: heap vacío\n");
    return -1;
  }
  return heap[1];
}

int extraer_max(int *heap, int *n) {
  if (*n == 0) {
    printf("Error: heap vacío\n");
    return -1;
  }
  int maximo = heap[1];
  heap[1] = heap[*n];
  (*n)--;
  hundir(1, heap, *n);
  return maximo;
}