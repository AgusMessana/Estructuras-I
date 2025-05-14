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
  BTree copia = btree_crear();
  copia = btree_copiar(raiz);
  int encontrado = btree_buscar(raiz, 5);
  int altura = btree_altura(raiz);
  int nodos_prof = btree_nnodos_profundidad(raiz, 1);
  int prof_nodo = btree_profundidad(raiz, 2);
  int suma_nodos = btree_suma(raiz);

  printf("Arbol original:\n");
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");

  printf("La cantidad de nodos es %d.\n", btree_nnodos(raiz));

  if (encontrado) {
    printf("El numero esta en el arbol.\n");
  } else {
    printf("El numero no esta en el arbol.\n");
  }

  printf("Arbol copiado:\n");
  btree_recorrer(copia, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");

  printf("La altura del arbol es %d\n", altura);

  printf("La cantidad de nodos a profundidad 1 es %d\n", nodos_prof);

  printf("El numero esta a profundidad %d\n", prof_nodo);

  printf("La suma de los valores de los nodos es %d\n", suma_nodos);


  btree_destruir(raiz);
  btree_destruir(copia);

  return 0;
}
