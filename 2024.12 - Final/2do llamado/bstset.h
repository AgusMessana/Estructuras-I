#ifndef __BSTSET_H__
#define __BSTSET_H__

typedef void (*FuncionVisitante)(int dato);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTSetRecorrido;

typedef struct bstNodo_ {
  int dato;
  struct bstNodo_ *der, *izq;
} bstNodo;

typedef bstNodo* BSTSet;

/**
 * Crea un BSTSet vacío.
 */
BSTSet crearBST();

/**
 * Agrega un elemento al conjunto. En caso de que el elemento ya exista, la operación no tiene ningún efecto sobre el conjunto.
 */
BSTSet agregarBST(BSTSet conj, int dato);

/**
 * Imprime todos los elementos del conjunto, sin repetir, y ordenados de menor a mayor.
 */
void imprimeBST(BSTSet conj);

/**
 * Calcula el conjunto resultado de la intersección de 2 conjuntos.
 */
BSTSet interseccionBST(BSTSet conj1, BSTSet conj2);

/**
 * Dado un conjunto y un entero k, devuelva el número presente en el conjunto más lejano a k (en valor absoluto, puede ser mayor o menor).
 */
int lejanoBST(BSTSet conj, int k);
#endif
