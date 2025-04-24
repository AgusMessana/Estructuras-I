#include <stdio.h>
#include <stdlib.h>
#include "arreglos.h"

ArregloEnteros *arreglo_enteros_crear(int capacidad) {
  ArregloEnteros *arreglo = (ArregloEnteros *) malloc(sizeof(ArregloEnteros));

  if (arreglo == NULL) {
    return NULL;
  }

  arreglo->datos = (int *) malloc(sizeof(int) * capacidad);

  arreglo->capacidad = capacidad;

  return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros * arreglo) {
  if (arreglo != NULL) {
    free(arreglo->datos);
    free(arreglo);
  }
}

int arreglo_enteros_leer(ArregloEnteros * arreglo, int pos) {
  int resultado;

  if (pos < 0 || pos >= arreglo->capacidad) {
    resultado = -1;
  } else {
    resultado = arreglo->datos[pos];
  }

  return resultado;
}

void arreglo_enteros_escribir(ArregloEnteros * arreglo, int pos, int dato) {
  if (pos < 0 || pos >= arreglo->capacidad) {
    return;
  }

  arreglo->datos[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros * arreglo) {
  return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros * arreglo) {
  for (int i = 0; i < arreglo->capacidad; i++) {
    printf("%d\n", arreglo->datos[i]);
  }
}

void arreglo_enteros_ajustar(ArregloEnteros * arreglo, int capacidad) {
  if (capacidad <= 0) {
    return;
  }

  int *temp = realloc(arreglo->datos, sizeof(int) * capacidad);

  arreglo->datos = temp;
  arreglo->capacidad = capacidad;
}

void arreglo_enteros_insertar(ArregloEnteros * arreglo, int pos, int dato) {
  if (pos < 0 || pos > arreglo->capacidad)
    return;

  int nueva_capacidad = arreglo->capacidad + 1;
  int *temp = realloc(arreglo->datos, sizeof(int) * nueva_capacidad);

  arreglo->datos = temp;

  int i = arreglo->capacidad - 1;
  while (i >= pos) {
    arreglo->datos[i + 1] = arreglo->datos[i];
    i = i - 1;
  }

  arreglo->datos[pos] = dato;
  arreglo->capacidad = nueva_capacidad;
}

void arreglo_enteros_eliminar(ArregloEnteros * arreglo, int pos) {
  if (pos < 0 || pos >= arreglo->capacidad)
    return;

  int i = pos;
  while (i < arreglo->capacidad - 1) {
    arreglo->datos[i] = arreglo->datos[i + 1];
    i = i + 1;
  }

  int nueva_capacidad = arreglo->capacidad - 1;
  int *temp = realloc(arreglo->datos, sizeof(int) * nueva_capacidad);

  if (temp != NULL || nueva_capacidad == 0) {
    arreglo->datos = temp;
    arreglo->capacidad = nueva_capacidad;
  }
}
