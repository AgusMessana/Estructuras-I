#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bsctree.h"

// Cuenta la cantidad de nodos azules y rojos.
static void contar_colores(ArbolBinarioColoreado a, int *rojos, int *azules) {
  if (a == NULL) {
    return;
  }

  if (a->colorNodo == Rojo) {
    (*rojos)++;
  } else if (a->colorNodo == Azul) {
    (*azules)++;
  }

  contar_colores(a->izq, rojos, azules);
  contar_colores(a->der, rojos, azules);
}

// Retorna el color del Arbol.
Color color(ArbolBinarioColoreado inicio) {
  int rojos = 0;
  int azules = 0;

  contar_colores(inicio, &rojos, &azules);
  if (rojos > azules) {
    return Rojo;
  } else if (azules > rojos) {
    return Azul;
  }

  return Neutro;
}

// Retorna 1 si el nodo es hoja y 0 si no lo es.
static int es_hoja(ArbolBinarioColoreado a) {
  return a != NULL && a->izq == NULL && a->der == NULL;
}

// Cuenta la cantidad de hojas puras que tiene el árbol
static int contar_puras_aux(ArbolBinarioColoreado a, Color objetivo,
                            int puro_hasta_aca) {
  int puro_ahora;
  if (a == NULL) {
    return 0;
  }

  if (puro_hasta_aca && a->colorNodo == objetivo) {
    puro_ahora = 1;
  } else {
    puro_ahora = 0;
  }

  if (es_hoja(a)) {
    if (puro_ahora) {
      return 1;
    } else {
      return 0;
    }
  }

  return contar_puras_aux(a->izq, objetivo, puro_ahora) +
      contar_puras_aux(a->der, objetivo, puro_ahora);
}

// Retorna la cantidad de hojas puras.
int CantidadPuras(ArbolBinarioColoreado inicio) {
  if (inicio == NULL) {
    return 0;
  }

  return contar_puras_aux(inicio, inicio->colorNodo, 1);
}
