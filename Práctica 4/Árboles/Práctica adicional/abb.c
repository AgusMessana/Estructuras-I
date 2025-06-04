#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "abb.h"

/**
 * Dado un entero k, busque en el árbol binario de búsqueda el menor
 * entero mayor a k.
 */
int bstree_cota_inferior(BSTree arbol, int k) {
  BSTree candidato = NULL;
  BSTree actual = arbol;
  while (actual != NULL) {
    if (actual->dato > k) {
      candidato = actual;
      actual = actual->izq;
    } else {
      actual = actual->der;
    }
  }
  return (candidato != NULL) ? candidato->dato : INT_MAX;
}

void bstree_recorrer_intervalo(BSTree arbol, int cota_inf, int cota_sup,
                               FuncionVisitante visit) {
  if (arbol == NULL) {
    return;
  }

  if (arbol->dato > cota_inf) {
    bstree_recorrer_intervalo(arbol->izq, cota_inf, cota_sup, visit);
  }
  if (arbol->dato >= cota_inf && arbol->dato <= cota_sup) {
    visit(arbol->dato);
  }
  if (arbol->dato < cota_sup) {
    bstree_recorrer_intervalo(arbol->der, cota_inf, cota_sup, visit);
  }
}
