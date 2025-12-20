#include "tablahash.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void *copia_str(void *dato) {
  assert(dato != NULL);
  const char *s = (const char *) dato;
  size_t n = strlen(s) + 1;
  char *c = malloc(n);
  assert(c != NULL);
  memcpy(c, s, n);
  return c;
}

static int comp_str(void *dato1, void *dato2) {
  assert(dato1 != NULL && dato2 != NULL);
  return strcmp((const char *) dato1, (const char *) dato2);
}

static void dest_str(void *dato) {
  free(dato);
}

static unsigned hash_str(void *dato) {
  assert(dato != NULL);
  return KRHash((char *) dato);
}

int main() {
  TablaHash tabla = tablahash_crear(4, copia_str, comp_str, dest_str, hash_str);
  assert(tabla != NULL);

  const char *palabras[] = {
    "hola", "chau", "casa", "perro", "gato", "auto", "avl", "hash",
    "rebalse", "tabla", "cordoba", "casilda", "hola", "hash", "avl"
  };
  size_t n = sizeof(palabras) / sizeof(palabras[0]);

  printf("Insertando %zu elementos (con duplicados)...\n", n);
  for (size_t i = 0; i < n; i++) {
    tablahash_insertar(tabla, (void *) palabras[i]);
  }

  /* --- TEST: verificar que están --- */
  assert(tablahash_contiene(tabla, "hola"));
  assert(tablahash_contiene(tabla, "avl"));
  assert(tablahash_contiene(tabla, "cordoba"));

  // Eliminamos algunos existentes
  printf("Eliminando existentes...\n");
  tablahash_eliminar(tabla, (void *) "hola");
  tablahash_eliminar(tabla, (void *) "avl");
  tablahash_eliminar(tabla, (void *) "cordoba");

  /* --- TEST: verificar que NO están --- */
  assert(!tablahash_contiene(tabla, "hola"));
  assert(!tablahash_contiene(tabla, "avl"));
  assert(!tablahash_contiene(tabla, "cordoba"));

  // Eliminamos no existentes (debe NO romper)
  printf("Eliminando no existentes...\n");
  tablahash_eliminar(tabla, (void *) "no-existe-1");
  tablahash_eliminar(tabla, (void *) "no-existe-2");

  /* --- TEST: siguen sin estar --- */
  assert(!tablahash_contiene(tabla, "no-existe-1"));
  assert(!tablahash_contiene(tabla, "no-existe-2"));

  // Volvemos a insertar para probar estabilidad post-eliminación
  printf("Reinsertando...\n");
  tablahash_insertar(tabla, (void *) "hola");
  tablahash_insertar(tabla, (void *) "cordoba");

  /* --- TEST: vuelven a estar --- */
  assert(tablahash_contiene(tabla, "hola"));
  assert(tablahash_contiene(tabla, "cordoba"));

  // Destrucción (ideal para correr con valgrind)
  printf("Destruyendo tabla...\n");
  tablahash_destruir(tabla);

  printf("OK\n");
  return 0;
}
