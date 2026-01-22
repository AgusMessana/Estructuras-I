#include "bstset.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Crea un BSTSet vacío
 */
BSTSet crearBST() {
  return NULL;
}

/**
 * Agrega un elemento al conjunto. En caso de que el elemento ya exista, la operación no tiene ningún efecto sobre el conjunto.
 */
BSTSet agregarBST(BSTSet conj, int dato) {
  if (conj == NULL) {           // insertar el dato en un nuevo nodo
    BSTSet nuevoNodo = malloc(sizeof(bstNodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = dato;
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  }
  if (dato < conj->dato) {      // dato < raiz->dato
    conj->izq = agregarBST(conj->izq, dato);
  } else if (dato > conj->dato) {       // raiz->dato < dato
    conj->der = agregarBST(conj->der, dato);
  }
  // Si el dato ya se encontraba, no es insertado
  return conj;
}

/**
 * Imprime todos los elementos del conjunto, sin repetir, y ordenados de menor a mayor.
 */
static void imprimir_intBST(int dato) {
  printf("%d\n", dato);
}

static void recorrerBST(BSTSet conj, BSTSetRecorrido orden,
                        FuncionVisitante visita) {
  if (conj != NULL) {
    if (orden == BTREE_RECORRIDO_PRE) {
      visita(conj->dato);
    }
    recorrerBST(conj->izq, orden, visita);
    if (orden == BTREE_RECORRIDO_IN) {
      visita(conj->dato);
    }
    recorrerBST(conj->der, orden, visita);
    if (orden == BTREE_RECORRIDO_POST) {
      visita(conj->dato);
    }
  }
}

void imprimeBST(BSTSet conj) {
  recorrerBST(conj, BTREE_RECORRIDO_IN, imprimir_intBST);
}

/**
 * Calcula el conjunto resultado de la intersección de 2 conjuntos.
 */
static int perteneceBST(BSTSet conj, int dato) {
  if (conj == NULL) {
    return 0;
  } else if (dato == conj->dato) {      // raiz->dato == dato
    return 1;
  } else if (dato < conj->dato) {       // dato < raiz->dato
    return perteneceBST(conj->izq, dato);
  } else {                      // raiz->dato < dato
    return perteneceBST(conj->der, dato);
  }
}

static void auxBST(BSTSet conj1, BSTSet conj2, BSTSet * res) {
  if (conj1 != NULL) {
    auxBST(conj1->izq, conj2, res);

    if (perteneceBST(conj2, conj1->dato) == 1) {
      *res = agregarBST(*res, conj1->dato);
    }

    auxBST(conj1->der, conj2, res);
  }
}

BSTSet interseccionBST(BSTSet conj1, BSTSet conj2) {
  BSTSet arbolRes = crearBST();
  auxBST(conj1, conj2, &arbolRes);
  return arbolRes;
}

/**
 * Dado un conjunto y un entero k, devuelva el número presente en el conjunto más lejano a k (en valor absoluto, puede ser mayor o menor).
 */
static int minBST(BSTSet conj) {
  while (conj->izq != NULL) {
    conj = conj->izq;
  }

  return conj->dato;
}

static int maxBST(BSTSet conj) {
  while (conj->der != NULL) {
    conj = conj->der;
  }

  return conj->dato;
}

static int absInt(int x) {
  if (x < 0) {
    return -x;
  }

  return x;
}

int lejanoBST(BSTSet conj, int k) {
  assert(conj != NULL);
  int min = minBST(conj);
  int max = maxBST(conj);

  if (absInt(min - k) >= absInt(max - k)) {
    return min;
  } else {
    return max;
  }
}
