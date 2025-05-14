#include "btree.h"
#include <assert.h>
#include <stdlib.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() {
  return NULL;
}

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) {
  return nodo == NULL;
}

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void inorder(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  inorder(arbol->left, visit);
  visit(arbol->dato);
  inorder(arbol->right, visit);
}

void preorder(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  visit(arbol->dato);
  inorder(arbol->left, visit);
  inorder(arbol->right, visit);
}

void postorder(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  postorder(arbol->left, visit);
  postorder(arbol->right, visit);
  visit(arbol->dato);
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  switch (orden) {
  case BTREE_RECORRIDO_IN:
    inorder(arbol, visit);
    break;
  case BTREE_RECORRIDO_PRE:
    preorder(arbol, visit);
    break;
  case BTREE_RECORRIDO_POST:
    postorder(arbol, visit);
    break;
  default:
    assert(0);
  }
}

int btree_nnodos(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }

  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

int btree_buscar(BTree arbol, int numero) {
  if (btree_empty(arbol)) {
    return 0;
  }
  if (arbol->dato == numero) {
    return 1;
  }

  return btree_buscar(arbol->left, numero)
      || btree_buscar(arbol->right, numero);
}

BTree btree_copiar(BTree arbol) {
  if (btree_empty(arbol)) {
    return NULL;
  }

  BTree copia_izq = btree_copiar(arbol->left);
  BTree copia_der = btree_copiar(arbol->right);

  return btree_unir(arbol->dato, copia_izq, copia_der);
}

int btree_altura(BTree arbol) {
  if (btree_empty(arbol)) {
    return -1;
  }
  int altura_izq = btree_altura(arbol->left);
  int altura_der = btree_altura(arbol->right);

  return 1 + (altura_izq > altura_der ? altura_izq : altura_der);
}

int btree_nnodos_profundidad(BTree arbol, int profundidad) {
  if (btree_empty(arbol)) {
    return 0;
  }
  if (profundidad == 0) {
    return 1;
  }
  int nodos_izq = btree_nnodos_profundidad(arbol->left, profundidad - 1);
  int nodos_der = btree_nnodos_profundidad(arbol->right, profundidad - 1);

  return nodos_izq + nodos_der;
}

int btree_profundidad(BTree arbol, int numero) {
  if (btree_empty(arbol)) {
    return -1;
  }
  if (arbol->dato == numero) {
    return 0;
  }

  int prof_izq = btree_profundidad(arbol->left, numero);
  int prof_der = btree_profundidad(arbol->right, numero);

  if (prof_izq == -1 && prof_der == -1) {
    return -1;
  }

  if (prof_izq == -1) {
    return 1 + prof_der;
  }
  if (prof_der == -1) {
    return 1 + prof_izq;
  }

  return (prof_izq < prof_der ? prof_izq : prof_der);
}

int btree_suma(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }
  
  return arbol->dato + btree_suma(arbol->left) + btree_suma(arbol->right);
}
