#include <stdio.h>
#include <stdlib.h>
#include "final.h"

/**
 * Cuenta la cantidad de nodos azules y rojos.
 */
static void contar_colores(ArbolBinarioColoreado arbol, int *rojos, int *azules) {
  if (arbol == NULL) {
    return;
  }

  if (arbol->colorNodo == Rojo) {
    (*rojos)++;
  } else if (arbol->colorNodo == Azul) {
    (*azules)++;
  }

  contar_colores(arbol->izq, rojos, azules);
  contar_colores(arbol->der, rojos, azules);
}

/**
 * Retorna el color del árbol.
 */
Color color(ArbolBinarioColoreado inicio) {
  int rojos = 0;
  int azules = 0;

  contar_colores(inicio, &rojos, &azules);
  if (rojos > azules) {
    return Rojo;
  } else if (azules > rojos) {
    return Azul;
  }

  // Si la cantidad de nodos rojos y azules son iguales, el árbol es Neutro.
  return Neutro;
}

/**
 * Retorna 1 si el nodo es una hoja y 0 si no lo es.
 */
static int es_hoja(ArbolBinarioColoreado arbol) {
  return arbol != NULL && arbol->izq == NULL && arbol->der == NULL;
}

/**
 * Cuenta la cantidad de hojas puras que tiene el árbol.
 */
static int contar_hojas_puras_aux(ArbolBinarioColoreado arbol, Color objetivo, int puro_hasta_aca) {
  int puro_ahora;
  if (arbol == NULL) {
    return 0;
  }

  if (puro_hasta_aca && arbol->colorNodo == objetivo) {
    puro_ahora = 1;
  } else {
    puro_ahora = 0;
  }

  if (es_hoja(arbol)) {
    if (puro_ahora) {
      return 1;
    } else {
      return 0;
    }
  }

  return contar_hojas_puras_aux(arbol->izq, objetivo, puro_ahora) + 
         contar_hojas_puras_aux(arbol->der, objetivo, puro_ahora);
}

/**
 * Retorna la cantidad de hojas puras.
 */
int CantidadPuras(ArbolBinarioColoreado inicio) {
  if (inicio == NULL) {
    return 0;
  }

  // El color objetivo es el mismo de la raiz porque, cuando una hoja es pura, todos sus ancestros
  // tienen el mismo color que ella, incluída la raiz del árbol.
  return contar_hojas_puras_aux(inicio, inicio->colorNodo, 1);
}
