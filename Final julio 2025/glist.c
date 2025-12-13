#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() {
  return NULL;
}

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) {
  return (list == NULL);
}

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode * node = list; node != NULL; node = node->next)
    visit(node->data);
}

/**
 * Elimina un elemento de la lista, si éste está.
 */
GList glist_eliminar(GList lista, void *dato, FuncionDestructora destr,
                     FuncionComparadora comp) {
  GList nodo = lista;
  if (lista == NULL) {
    return lista;
  }
  if (comp(nodo->data, dato) == 0) {
    lista = lista->next;
    destr(nodo->data);
    free(nodo);
    return lista;
  }

  GList ant = NULL;
  while (nodo != NULL && comp(nodo->data, dato) != 0) {
    ant = nodo;
    nodo = nodo->next;
  }
  if (nodo != NULL) {
    ant->next = nodo->next;
    destr(nodo->data);
    free(nodo);
  }

  return lista;
}
