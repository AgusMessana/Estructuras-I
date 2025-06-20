#include <stdio.h>
#include <stdlib.h>
#include "Ej2.h"

void *no_copia(void *dato) {
  return dato;
}

AVL crear_nodo(void *dato) {
  AVL arbol = malloc(sizeof(struct _AVL_Nodo));
  arbol->dato = no_copia(dato);
  arbol->izq = NULL;
  arbol->der = NULL;
  arbol->altura = 1;

  return arbol;
}

int altura(AVL arbol) {
  if (arbol == NULL) {
    return 0;
  }
  return arbol->altura;
}

int actualizar_altura(AVL arbol) {
  if (arbol == NULL) {
    return;
  }
  int alt_izq = altura(arbol->izq);
  int alt_der = altura(arbol->der);

  arbol->altura = 1 + (alt_izq > alt_der ? alt_izq : alt_der);
}

AVL principal_aux(void **arr, int inicio, int fin) {
  if (inicio > fin) {
    return NULL;
  }

  int medio = inicio + (fin - inicio) / 2;
  AVL raiz = crear_nodo(arr[medio]);
  if (raiz == NULL) {
    return NULL;
  }

  raiz->izq = principal_aux(arr, inicio, medio - 1);
  raiz->der = principal_aux(arr, medio + 1, fin);

  actualizar_altura(raiz);

  return raiz;
}

AVL sorted_arr_to_avl(void **arr, int n) {
  if (arr == NULL || n <= 0) {
    return NULL;
  }
  return principal_aux(arr, 0, n - 1);
}
