#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "1er_parcial_2024.h"

// Ejercicio 1
GArray listToArray(GList lista, FuncionCopia c) {
  if (glist_vacia(lista)) {
    return NULL;
  }

  int capacidad = 4;
  int cantidad = 0;
  GArray arr = malloc(capacidad * sizeof(void *));
  if (!arr) {
    return NULL;
  }

  for (GNode * temp = lista; temp != NULL; temp = temp->next) {
    if (cantidad == capacidad) {
      capacidad *= 2;
      void **nuevo_arr = realloc(arr, capacidad * sizeof(void *));
      if (!nuevo_arr) {
        free(arr);
        return NULL;
      }
      arr = nuevo_arr;
    }
    arr[cantidad++] = c(temp->data);
  }

  void **final_arr = realloc(arr, (cantidad + 1) * sizeof(void *));
  if (final_arr) {
    arr = final_arr;
  }
  arr[cantidad] = NULL;

  return arr;
}

// Ejercicio 2
void *copiar_persona(void *dato) {
  return dato;                  // No copia nada, solo devuelve el puntero
}

GArray listToArrayPersona(GList lista) {
  return listToArray(lista, copiar_persona);
}

// Ejercicio 3
int mas18ConA(void *dato) {
  Persona *p = (Persona *) dato;
  for (int i = 0; p->direccion[i] != '\0'; i++) {
    if (toupper(p->direccion[i]) == 'A' && p->edad >= 18) {
      return 1;
    }
  }

  return 0;
}

GList glist_filtrar(GList lista, Predicado p, FuncionCopia c) {
  if (glist_vacia(lista)) {
    return NULL;
  }
  GList nuevaLista = glista_crear();
  for (GNode * temp = lista; temp != NULL; temp = temp->next) {
    if (p(temp->data)) {
      nuevaLista = glist_agregar_inicio(nuevaLista, temp->data, c);
    }
  }

  return nuevaLista;
}

GList mayores18ConA(GList lista) {
  return glist_filtrar(lista, mas18ConA, copiar_persona);
}
