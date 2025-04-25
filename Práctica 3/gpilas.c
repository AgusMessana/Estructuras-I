#include <stdio.h>
#include <stdlib.h>
#include <gplias.h>

Pila gpila_crear() {
  return NULL;
}

void gpila_destruir(Pila pila, FuncionDestructora destroy) {
  glist_destruir(pila, destroy);
}

int gpila_es_vacia(Pila pila) {
  return pila == NULL;
}

void *gpila_tope(Pila pila) {
  return glist_primero(pila);
}

Pila gpila_apilar(Pila pila, void *elemento, FuncionCopia copy) {
  return glist_agregar_inicio(pila, elemento, copy);
}

Pila gpila_desapilar(Pila pila, FuncionDestructora destroy) {
  return glist_eliminar_primero(pila, destroy);
}

void gpila_imprimir(Pila pila, FuncionVisitante visit) {
  glist_recorrer(pila, visit);
}
