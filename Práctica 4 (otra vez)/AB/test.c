#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");

  int nnodos_arbol = btree_nnodos(raiz);
  int valor = 5;
  int profundidad = 1;
  int esta_valor = btree_buscar(raiz, valor);
  int altura = btree_altura(raiz);
  int nodos_profundidad_dada = btree_nnodos_profundidad(raiz, profundidad);
  int suma = btree_sumar(raiz);
  BTree copia = btree_copiar(raiz);
  printf("La cantidad de nodos del árbol es %d.\n", nnodos_arbol);
  if (esta_valor == 0) {
    printf("El valor %d no está en el árbol.\n", valor);
  } else {
    printf("El valor %d está en el árbol.\n", valor);
  }
  btree_recorrer(copia, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  printf("La altura del árbol es %d.\n", altura);
  printf("Los cantidad de nodos a profundidad %d es %d.\n", profundidad,
         nodos_profundidad_dada);
  printf("La suma de los valores del árbol es %d.\n", suma);
  btree_destruir(raiz);

  return 0;
}
