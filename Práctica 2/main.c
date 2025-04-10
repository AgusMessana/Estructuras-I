#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

static int comparar_enteros(int dato1, int dato2) {
  if(dato1 == dato2) {
    return 1;
  }
  return 0;
}

static int ordenar_enteros(int dato1, int dato2) {
  return dato1 - dato2;
}

int main(int argc, char* argv[]) {
  SList lista1 = slist_crear();
  SList lista2 = slist_crear();

  lista1 = slist_agregar_inicio(lista1, 3);
  lista1 = slist_agregar_inicio(lista1, 2);
  lista1 = slist_agregar_inicio(lista1, 1);
  lista1 = slist_agregar_final(lista1, 4);
  lista1 = slist_agregar_final(lista1, 9);
  lista1 = slist_agregar_final(lista1, 14);

  lista2 = slist_agregar_inicio(lista2, 100);
  lista2 = slist_agregar_inicio(lista2, 2);
  lista2 = slist_agregar_inicio(lista2, 2000);
  lista2 = slist_agregar_final(lista2, -10);

  slist_destruir(lista1);
  slist_destruir(lista2);

  return 0;
}
