#include "tablahash.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void *copia_str(void *dato) {
  assert(dato != NULL);
  const char *s = (const char *)dato;
  size_t n = strlen(s) + 1;
  char *c = malloc(n);
  assert(c != NULL);
  memcpy(c, s, n);
  return c;
}

static int comp_str(void *dato1, void *dato2) {
  assert(dato1 != NULL && dato2 != NULL);
  return strcmp((const char *)dato1, (const char *)dato2);
}

static void dest_str(void *dato) {
  free(dato);
}

static unsigned hash_str(void *dato) {
  assert(dato != NULL);
  return KRHash((const char *)dato);
}

static int tablahash_contiene_local(TablaHash tabla, void *dato) {
  return tablahash_buscar(tabla, dato) != NULL;
}

int main(void) {
  TablaHash tabla = tablahash_crear(4, copia_str, comp_str, dest_str, hash_str);
  assert(tabla != NULL);

  const char *palabras[] = {
    "hola", "chau", "casa", "perro", "gato", "auto", "avl", "hash",
    "rebalse", "tabla", "cordoba", "casilda", "hola", "hash", "avl"
  };
  size_t n = sizeof(palabras) / sizeof(palabras[0]);

  printf("Capacidad inicial: %u\n", tablahash_capacidad(tabla));

  unsigned cap_prev = tablahash_capacidad(tabla);

  printf("Insertando %zu elementos (con duplicados)...\n", n);
  for (size_t i = 0; i < n; i++) {
    tablahash_insertar_balance(tabla, (void *)palabras[i]);

    unsigned cap_now = tablahash_capacidad(tabla);
    if (cap_now != cap_prev) {
      printf("Rehash! nueva capacidad = %u (tras insertar '%s')\n",
             cap_now, palabras[i]);
      cap_prev = cap_now;
    }
  }

  printf("Capacidad final: %u | numElems: %u\n",
         tablahash_capacidad(tabla), tablahash_numElems(tabla));

  /* --- TEST: verificar que están --- */
  assert(tablahash_contiene_local(tabla, (void *)"hola"));
  assert(tablahash_contiene_local(tabla, (void *)"avl"));
  assert(tablahash_contiene_local(tabla, (void *)"cordoba"));

  printf("Eliminando existentes...\n");
  tablahash_eliminar(tabla, (void *)"hola");
  tablahash_eliminar(tabla, (void *)"avl");
  tablahash_eliminar(tabla, (void *)"cordoba");

  assert(!tablahash_contiene_local(tabla, (void *)"hola"));
  assert(!tablahash_contiene_local(tabla, (void *)"avl"));
  assert(!tablahash_contiene_local(tabla, (void *)"cordoba"));

  printf("Eliminando no existentes...\n");
  tablahash_eliminar(tabla, (void *)"no-existe-1");
  tablahash_eliminar(tabla, (void *)"no-existe-2");

  assert(!tablahash_contiene_local(tabla, (void *)"no-existe-1"));
  assert(!tablahash_contiene_local(tabla, (void *)"no-existe-2"));

  printf("Reinsertando...\n");
  tablahash_insertar_balance(tabla, (void *)"hola");
  tablahash_insertar_balance(tabla, (void *)"cordoba");

  assert(tablahash_contiene_local(tabla, (void *)"hola"));
  assert(tablahash_contiene_local(tabla, (void *)"cordoba"));

  printf("Destruyendo tabla...\n");
  tablahash_destruir(tabla);

  printf("OK\n");
  return 0;
}

// gcc -Wall -Wextra -g main.c tablahash.c glist.c utils.c -o prueba