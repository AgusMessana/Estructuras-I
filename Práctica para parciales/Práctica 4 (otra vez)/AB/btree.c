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
 * Funciones auxiliares para la función recorrer
 */
void preorder(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  visit(arbol->dato);
  preorder(arbol->left, visit);
  preorder(arbol->right, visit);
}

void inorder(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  inorder(arbol->left, visit);
  visit(arbol->dato);
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

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  switch (orden) {
  case BTREE_RECORRIDO_PRE:
    preorder(arbol, visit);
    break;
  case BTREE_RECORRIDO_IN:
    inorder(arbol, visit);
    break;
  case BTREE_RECORRIDO_POST:
    postorder(arbol, visit);
    break;
  default:
    assert(0);
  }
  return;
}

/**
 * Retorna el número de nodos del árbol.
 */
int btree_nnodos(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }

  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

/**
 * Retorna 1 si el número dado se encuentra en el árbol, y 0 en caso contrario.
 */
int btree_buscar(BTree arbol, int dato) {
  if (btree_empty(arbol)) {
    return 0;
  }
  if (arbol->dato == dato) {
    return 1;
  }

  return btree_buscar(arbol->left, dato) || btree_buscar(arbol->right, dato);
}

/**
 * Retorna un nuevo árbol que sea una copia del árbol dado.
 */
BTree btree_copiar(BTree arbol) {
  if (btree_empty(arbol)) {
    return NULL;
  }
  BTree copiaArbol = malloc(sizeof(struct _BTNodo));
  copiaArbol->dato = arbol->dato;
  copiaArbol->left = btree_copiar(arbol->left);
  copiaArbol->right = btree_copiar(arbol->right);

  return copiaArbol;
}

/**
 * Retorna la áltura del árbol.
 */
int btree_altura(BTree arbol) {
  if (btree_empty(arbol)) {
    return -1;
  }
  int altura_izq = btree_altura(arbol->left);
  int altura_der = btree_altura(arbol->right);

  return 1 + (altura_izq > altura_der ? altura_izq : altura_der);
}

/**
 * Retorna el número de nodos que se encuentran a la profundidad dada.
 */
int btree_nnodos_profundidad(BTree arbol, int profundidad) {
  if (btree_empty(arbol) || profundidad < 0) {
    return 0;
  }
  if (profundidad == 0) {
    return 1;
  }

  int nodos_izq = btree_nnodos_profundidad(arbol->left, profundidad - 1);
  int nodos_der = btree_nnodos_profundidad(arbol->right, profundidad - 1);

  return nodos_izq + nodos_der;
}

/**
 * Retorna la profundidad del nodo que contiene el número dado, y -1 si el
 * número no se encuentra en el árbol.
 */
int btree_profundidad(BTree arbol, int dato) {
  if (btree_empty(arbol)) {
    return -1;
  }
  if (arbol->dato == dato) {
    return 0;
  }

  int prof_izq = btree_profundidad(arbol->left, dato);
  int prof_der = btree_profundidad(arbol->right, dato);

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

/**
 * Retorna la suma total de los datos del árbol.
 */
int btree_sumar(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }

  return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
}


