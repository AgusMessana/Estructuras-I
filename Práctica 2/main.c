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

int main(int argc, char* argv[]) {
  SList lista1 = slist_crear();
  SList lista2 = slist_crear();

  lista1 = slist_agregar_inicio(lista1, 3);
  lista1 = slist_agregar_inicio(lista1, 2);
  lista1 = slist_agregar_inicio(lista1, 1);
  lista1 = slist_agregar_final(lista1, 4);

  lista2 = slist_agregar_inicio(lista2, 4);
  lista2 = slist_agregar_inicio(lista2, 7);
  lista2 = slist_agregar_inicio(lista2, 2);
  lista2 = slist_agregar_final(lista2, 9);

  slist_recorrer(lista1, imprimir_entero);
  puts("");

  slist_recorrer(lista2, imprimir_entero);
  puts("");

  SList comunes = slist_intersecar_custom(lista1, lista2, comparar_enteros);
  slist_recorrer(comunes, imprimir_entero);
  puts("");

  slist_destruir(lista1);
  slist_destruir(lista2);
  slist_destruir(comunes);

  return 0;
}
