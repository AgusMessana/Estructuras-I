#include <stdio.h>
#include <stdlib.h>
#include "ab.h"

/**
 * Dado un arbol binario, genere el arbol binario espejo, donde el hijo
 * derecho de cada nodo pasa a ser izquierdo y el izquierdo pasa a ser
 * derecho.
 */
BTree mirror(BTree arbol) {
  if (arbol == NULL) {
    return NULL;
  }

  BTree nuevoNodo = malloc(sizeof(BTNodo));
  nuevoNodo->dato = arbol->dato;

  nuevoNodo->left = mirror(arbol->right);
  nuevoNodo->right = mirror(arbol->left);

  return nuevoNodo;
}

Cola *crear_cola(int capacidad) {
  Cola *cola = (Cola *) malloc(sizeof(Cola));
  cola->array = malloc(capacidad * sizeof(BTNodo *));
  cola->frente = 0;
  cola->final = -1;
  cola->capacidad = capacidad;
  return cola;
}

void encolar(Cola * cola, BTNodo * nodo) {
  if (cola->final == cola->capacidad - 1)
    return;
  cola->array[++cola->final] = nodo;
}

BTNodo *desencolar(Cola * cola) {
  if (cola->frente > cola->final)
    return NULL;
  return cola->array[cola->frente++];
}

/**
 * Determina si el árbol es completo o no. Devuelve 1 si lo es y 0 si no.
 */
int btree_es_completo(BTree arbol) {
  if (arbol == NULL) {
    return 1;
  }
  Cola *cola = crear_cola(100);
  encolar(cola, arbol);
  int encontrado_null = 0;

  while (cola->frente <= cola->final) {
    BTNodo *actual = desencolar(cola);

    if (actual == NULL) {
      encontrado_null = 1;
    } else {
      if (encontrado_null) {
        free(cola->array);
        free(cola);
        return 0;
      }
      encolar(cola, actual->left);
      encolar(cola, actual->right);
    }
  }
  free(cola->array);
  free(cola);
  return 1;
}
