#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "grafo.h"

typedef struct _Nodo {
  int col;
  struct _Nodo *sig;
} Nodo;

typedef Nodo *SList;

/**
 * Crea una matriz esparsa
 */
MatrizEsparsa *matriz_crear(int n) {
  MatrizEsparsa *m = malloc(sizeof(MatrizEsparsa));
  assert(m != NULL);

  m->n = n;
  m->filas = malloc(sizeof(SList) * n);
  assert(m->filas != NULL);

  for (int i = 0; i < n; ++i) {
    m->filas[i] = NULL;
  }

  return m;
}

/**
 * Destruye una matriz esparsa
 */
void matriz_destruir(MatrizEsparsa * m) {
  for (int i = 0; i < m->n; ++i) {
    Nodo *act = m->filas[i];
    while (act != NULL) {
      Nodo *sig = act->sig;
      free(act);
      act = sig;
    }
  }

  free(m->filas);
  free(m);
}

/**
 * Inserta un 1 en la posición (i, j)
 */
void matriz_insertar(MatrizEsparsa * m, int i, int j) {
  if (i < 0 || i >= m->n || j < 0 || j >= m->n) {
    return;
  }

  Nodo *actual = m->filas[i];
  while (actual != NULL) {
    if (actual->col == j) {
      return;
    }

    actual = actual->sig;
  }

  Nodo *nuevo = malloc(sizeof(Nodo));
  assert(nuevo != NULL);
  nuevo->col = j;
  nuevo->sig = m->filas[i];
  m->filas[i] = nuevo;
}

/**
 * Elimina el 1 en la posición (i, j)
 */
void matriz_eliminar(MatrizEsparsa * m, int i, int j) {
  if (i < 0 || i >= m->n || j < 0 || j >= m->n) {
    return;
  }

  Nodo *act = m->filas[i];
  Nodo *ant = NULL;

  while (act != NULL) {
    if (act->col == j) {        // Hay un 1 en la posición (i, j)
      if (ant == NULL) {        // Indica si es el primer valor de la lista
        m->filas[i] = act->sig; // Eliminamos el primer elemento
      } else {
        ant->sig = act->sig;    // Eliminamos algún valor en el medio o el último.
      }

      free(act);
      return;
    }

    ant = act;
    act = act->sig;
  }
}

/**
 * Devuelve 1 si hay un 1 en (i, j) y 0 si no
 */
int matriz_contiene(MatrizEsparsa * m, int i, int j) {
  if (i < 0 || i >= m->n || j < 0 || j >= m->n) {
    return 0;
  }

  Nodo *act = m->filas[i];
  while (act != NULL) {
    if (act->col == j) {
      return 1;                 //Está
    }

    act = act->sig;
  }

  return 0;                     // No está
}

/**
 * Devuelve 1 si la matriz esparsa es simétrica y 0 si no
 */
int matriz_es_simetrica(MatrizEsparsa * m) {
  for (int i = 0; i < m->n; i++) {
    Nodo *act = m->filas[i];
    while (act != NULL) {
      int j = act->col;

      if (matriz_contiene(m, j, i) == 0) {
        return 0;               // Existe (i, j) pero no (j, i)
      }

      act = act->sig;
    }
  }

  return 1;
}

/**
 * Marca cada vecino de una fila
 */
void dfs (MatrizEsparsa *m, int u, int *visitado) {
  Nodo *act = m->filas[u];
  while(act != NULL) {
    int v = act->col;
    if(visitado[v] == 0) {
      visitado[v] == 1;
      dfs(m, v, visitado);
    }

    act = act->sig;
  }
}

/**
 * Devuelve la cantidad de índices con los que se relaciona uno
 * dado, en uno o más pasos.
 */
int r_kleen(MatrizEsparsa * m, int indice) {
  if(indice < 0 || indice >= m->n) {
    return 0;
  }

  int *visitado = calloc(m->n, sizeof(int));
  assert(visitado != NULL);

  visitado[indice] = 1;
  dfs(m, indice, visitado);

  int contador = 0;
  for(int i = 0; i < m->n; i++) {
    if(visitado[i] == 1 && i != indice) {
      contador++;
    }
  }

  free(visitado);
  return contador;
}
