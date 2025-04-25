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

GList glist_filtrar(GList lista, Predicado p, FuncionCopia c) {
  GList nuevaLista = glist_crear();
  for (GNode * temp = lista; temp != NULL; temp = temp->next) {
    if (p(temp->data)) {
      nuevaLista = glist_agregar_inicio(nuevaLista, temp->data, c);
    }
  }
  return nuevaLista;
}

// Listas generales ordenadas
SGList sglist_crear() {
  return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora dest) {
  GNode *nodoAeliminar;
  while (lista != NULL) {
    nodoAeliminar = lista;
    lista = lista->next;
    dest(nodoAeliminar->data);
    free(nodoAeliminar);
  }
}

int sglist_vacia(SGList lista) {
  return (lista == NULL);
}

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copy,
                       FuncionComparadora comp) {
  GNode *nuevoNodo = malloc(sizeof(GNode));
  nuevoNodo->data = copy(dato);
  if (lista == NULL || comp(dato, lista->data) < 0) {
    nuevoNodo->next = lista;
    return nuevoNodo;
  }
  GNode *actual = lista;
  while (actual->next != NULL && comp(dato, actual->next->data) >= 0) {
    actual = actual->next;
  }
  nuevoNodo->next = actual->next;
  actual->next = nuevoNodo;

  return lista;
}

int sglist_buscar(SGList lista, void *dato, FuncionComparadora comp) {
  int encontrado = 0;
  for (GNode * temp = lista; temp != NULL && encontrado != 1; temp = temp->next) {
    if (comp(dato, temp->data) == 0) {
      encontrado = 1;
    }
  }
  return encontrado;
}

SGList sglist_arr(void **arreglo, int longi, FuncionCopia copy,
                  FuncionComparadora comp) {
  SGList listaArr = sglist_crear();
  for (int i = 0; i < longi; i++) {
    void *copia = copy(arreglo[i]);
    listaArr = sglist_insertar(listaArr, copia, copy, comp);
  }
  return listaArr;
}

void *glist_primero(GList lista) {
  assert(lista != NULL);
  return lista->data;
}

GList glist_eliminar_primero(GList lista, FuncionDestructora destroy) {
  if (lista == NULL) {
    return NULL;
  }

  GList siguiente = lista->next;
  destroy(lista->data);
  free(lista);
  return siguiente;
}
