#include "btree.h"
#include <assert.h>
#include <stdlib.h>

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

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
  preorder(arbol->left, visit);
  preorder(arbol->right, visit);
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

/**
 * Recorrido del arbol preorder iterativo, utilizando la funcion pasada.
 */
void *no_copia(void *dato) {
  return dato;
}

void no_destruir(void *dato) {
  return;
}

/* void btree_recorrer_pre_it(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol))
    return;

  Pila pila_de_nodos = pila_crear();

  pila_de_nodos = pila_apilar(pila_de_nodos, arbol, no_copia);

  while (!pila_vacia(pila_de_nodos)) {

    BTree nodo_actual = pila_tope(pila_de_nodos, no_copia);
    visit(nodo_actual->dato);

    pila_de_nodos = pila_desapilar(pila_de_nodos, no_destruir);

    if (!btree_empty(nodo_actual->right))
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->right, no_copia);

    if (!btree_empty(nodo_actual->left))
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->left, no_copia);
  }

  pila_destruir(pila_de_nodos, no_destruir);

} */

// Retorna el número de nodos del árbol.
int btree_nnodos(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }

  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

// Retorna 1 si el número dado se encuentra en el árbol, y 0 en caso contrario.
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

// Retorna un nuevo árbol que sea una copia del árbol dado.
BTree btree_copiar(BTree arbol) {
  if (btree_empty(arbol)) {
    return NULL;
  }

  BTree copia_izq = btree_copiar(arbol->left);
  BTree copia_der = btree_copiar(arbol->right);

  return btree_unir(arbol->dato, copia_izq, copia_der);
}

// Retorna la altura del árbol.
int btree_altura(BTree arbol) {
  if (btree_empty(arbol)) {
    return -1;
  }
  int altura_izq = btree_altura(arbol->left);
  int altura_der = btree_altura(arbol->right);

  return 1 + (altura_izq > altura_der ? altura_izq : altura_der);
}

// Retorna el número de nodos que se encuentran a la profundidad dada.
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

// Retrona la profundidad del nodo que contiene el número dado, y -1 si el número no se encuentra en el árbol.
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

// Retorna la suma totoal de los datos del árbol.
int btree_suma(BTree arbol) {
  if (btree_empty(arbol)) {
    return 0;
  }

  return arbol->dato + btree_suma(arbol->left) + btree_suma(arbol->right);
}

// Recorrido del arbol, utilizando la funcion pasada.
void inorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra, void *extra) {
  if (btree_empty(arbol)) {
    return;
  }
  inorder_extra(arbol->left, visit_extra, extra);
  visit_extra(arbol->dato, extra);
  inorder_extra(arbol->right, visit_extra, extra);
}

void preorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra, void *extra) {
  if (btree_empty(arbol)) {
    return;
  }
  visit_extra(arbol->dato, extra);
  preorder_extra(arbol->left, visit_extra, extra);
  preorder_extra(arbol->right, visit_extra, extra);
}

void postorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra,
                     void *extra) {
  if (btree_empty(arbol)) {
    return;
  }
  postorder_extra(arbol->left, visit_extra, extra);
  postorder_extra(arbol->right, visit_extra, extra);
  visit_extra(arbol->dato, extra);
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit_extra, void *extra) {
  switch (orden) {
  case BTREE_RECORRIDO_IN:
    inorder_extra(arbol, visit_extra, extra);
    break;
  case BTREE_RECORRIDO_PRE:
    preorder_extra(arbol, visit_extra, extra);
    break;
  case BTREE_RECORRIDO_POST:
    postorder_extra(arbol, visit_extra, extra);
    break;
  default:
    assert(0);
  }
}

//Retorna el número de nodos del árbol con un dato extra.
void contar_nodo(int dato, void *extra) {
  int *contador = (int *)extra;
  (*contador)++;
}

int btree_nnodos_extra(BTree arbol) {
  int contador = 0;
  btree_recorrer_extra(arbol, BTREE_RECORRIDO_POST, contar_nodo, &contador);
  return contador;
}

// Retorna la suma totoal de los datos del árbol con un dato extra.
void sumar_dato(int dato, void *extra) {
  int *acumulador = (int *)extra;
  *acumulador += dato;
}

int btree_suma_extra(BTree arbol) {
  int suma = 0;
  btree_recorrer_extra(arbol, BTREE_RECORRIDO_POST, sumar_dato, &suma);
  
  return suma;
}

// void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit){
//   if(btree_empty(arbol)){
//     return;
//   }
  
//   Cola* cola = cola_crear();
//   cola_encolar(cola, arbol, no_copia);

//   while(!cola_es_vacia(cola)){
//     BTree nodo_actual = (BTree)cola_desencolar(cola, no_destruir);
//     visit(nodo_actual->dato);

//     if(!btree_empty(nodo_actual->left)){
//       cola_encolar(cola, nodo_actual->left, no_copia);
//     }
//     if(!btree_empty(nodo_actual->right)){
//       cola_encolar(cola, nodo_actual->right, no_copia);
//     }
//   }

//   cola_destruir(cola, no_destruir);
// }