#include <stdio.h>
#include <stdlib.h>
#include <gpilas.h>

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

GList invertir_orden(GList lista, FuncionCopia copy, FuncionDestructora destroy) {
  Pila nuevaPila = gpila_crear();
  for (GNode * temp = lista; temp != NULL; temp = temp->next) {
    nuevaPila = gpila_apilar(nuevaPila, temp->data, copy);
  }
  GList listaInvertida = glist_crear();
  while (!gpila_es_vacia(nuevaPila)) {
    listaInvertida =
        glist_agregar_inicio(listaInvertida, gpila_tope(nuevaPila), copy);
    nuevaPila = gpila_desapilar(nuevaPila, destroy);
  }
  gpila_destruir(nuevaPila, destroy);
  return listaInvertida;
}
