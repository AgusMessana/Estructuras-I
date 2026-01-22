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
 * Devuelve 1 si el elemento está en la lista, y 0 si no está.
 */
int glist_esta(GList lista, void *dato, FuncionComparadora comp) {
  GList nodo = lista;
  while (nodo != NULL) {
    if (comp(nodo->data, dato) == 0) {
      return 1;
    }
    nodo = nodo->next;
  }

  return 0;
}

/**
 * Devuelve el dato pasado si está y NULL en caso contrario
 */
void *glist_dato_esta(GList lista, void *dato, FuncionComparadora comp) {
  GList nodo = lista;
  while (nodo != NULL) {
    if (comp(nodo->data, dato) == 0) {
      return nodo->data;
    }
    nodo = nodo->next;
  }

  return NULL;
}

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopiadora copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Elimina el elemento pasado de la lista.
 */
GList glist_eliminar(GList lista, void *dato, FuncionComparadora comp,
                     FuncionDestructora destr) {
  GList actual = lista;
  GList ant = NULL;
  while (actual != NULL && comp(actual->data, dato) != 0) {
    ant = actual;
    actual = actual->next;
  }

  if (actual == NULL) {
    return lista;
  }

  if (ant == NULL) {
    GList nuevo = lista->next;
    destr(actual->data);
    free(actual);
    return nuevo;
  }

  ant->next = actual->next;
  destr(actual->data);
  free(actual);
  return lista;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode * node = list; node != NULL; node = node->next)
    visit(node->data);
}
