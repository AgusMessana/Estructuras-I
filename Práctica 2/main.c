#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char* argv[]) {
  SList lista1 = slist_crear();
  lista1 = slist_agregar_inicio(lista1, 3);
  lista1 = slist_agregar_inicio(lista1, 2);
  lista1 = slist_agregar_inicio(lista1, 1);
  lista1 = slist_agregar_final(lista1, 4);

  slist_recorrer(lista1, imprimir_entero);
  puts("");

  slist_insertar(&lista1, 83, 2);

  slist_recorrer(lista1, imprimir_entero);
  puts("");

  slist_destruir(lista1);

  return 0;
}
