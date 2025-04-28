#include <stdio.h>
#include <stdlib.h>
#include "colas.h"

Cola *cola_crear() {
  Cola *nuevaCola = malloc(sizeof(Cola));
  if (nuevaCola == NULL) {
    return NULL;
  }
  nuevaCola->primero = NULL;
  nuevaCola->ultimo = NULL;

  return nuevaCola;
}

void cola_destruir(Cola * cola, FuncionDestructora destroy) {
  if (cola != NULL) {
    glist_destruir(cola->primero, destroy);
    free(cola);
  }
}

int cola_es_vacia(Cola * cola) {
  if (cola == NULL) {
    return 1;
  }
  return glist_vacia(cola->primero);
}

void *cola_inicio(Cola * cola) {
  if (cola == NULL || cola->primero == NULL) {
    return NULL;
  }
  return cola->primero->data;
}

Cola *cola_encolar(Cola * cola, void *elemento, FuncionCopia copy) {
  if (cola == NULL) {
    return NULL;
  }
  cola->ultimo = glist_agregar_final(cola->ultimo, elemento, copy);
  if (cola->primero == cola->ultimo) {
    cola->primero = cola->ultimo;
  }
}

Cola *cola_desencolar(Cola * cola, FuncionDestructora destroy) {
  if (cola == NULL || cola->primero == NULL) {
    return NULL;
  }

  cola->primero = glist_eliminar_primero(cola->primero, destroy);

  if (cola->primero == NULL) {
    cola->ultimo = NULL;
  }

  return cola;
}

void cola_imprimir(Cola * cola, FuncionVisitante visit) {
  if (cola == NULL || cola->primero == NULL) {
    return;
  }
  glist_recorrer(cola->primero, visit);
}
