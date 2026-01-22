#include "tablahash.h"
#include "avl.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  unsigned char inicial;
  unsigned cantElems;
  AVL arbol;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned capacidad;
  unsigned numElems;
};

// Creación
/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear() {
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);

  tabla->capacidad = 256;
  tabla->numElems = 0;

  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad);
  assert(tabla->elems != NULL);

  for (int idx = 0; idx < 256; idx++) {
    tabla->elems[idx].inicial = (unsigned char) idx;
    tabla->elems[idx].arbol = NULL;
  }

  return tabla;
}

// Inserción
/**
 * Estructura palabra, necesaria para insertar en cada AVL.
 */
typedef struct {
  char *palabra;
  int cuenta;
} Palabra;

/**
 * Funciones auxiliares para comparar en árboles
 */
int palabra_comp(void *a, void *b) {
  Palabra *p1 = a;
  Palabra *p2 = b;
  return strcmp(p1->palabra, p2->palabra);
}

void *palabra_copia(void *dato) {
  Palabra *p = dato;
  Palabra *n = malloc(sizeof(Palabra));

  n->palabra = malloc(strlen(p->palabra) + 1);
  strcpy(n->palabra, p->palabra);

  n->cuenta = p->cuenta;
  return n;
}

void palabra_destr(void *dato) {
  Palabra *p = dato;
  free(p->palabra);
  free(p);
}

/**
 * Inserta un dato en la tabla.
 */
void tablahash_insertar(TablaHash tabla, const char *pal) {
  assert(tabla != NULL);
  assert(pal != NULL);

  unsigned char idx = (unsigned char) pal[0];
  CasillaHash *bucket = &tabla->elems[idx];

  // Si el AVL del bucket no está creado, lo creamos
  if (bucket->arbol == NULL) {
    bucket->arbol = avl_crear(palabra_copia, palabra_comp, palabra_destr);
  }
  // Buscamos la palabra
  Palabra key;
  key.palabra = (char *) pal;
  key.cuenta = 0;

  Palabra *p = avl_buscar_dato(bucket->arbol, &key);

  if (p) {                      // La palabra ya está en el árbol. Aumentamos su contador.
    p->cuenta++;
    bucket->cantElems++;
  } else {                      // La palabra no está en el árbol. La agregamos.
    Palabra nuevo;
    nuevo.palabra = (char *) pal;
    nuevo.cuenta = 1;

    avl_insertar(bucket->arbol, &nuevo);
    bucket->cantElems++;
    tabla->numElems++;
  }
}

// Búsqueda por caracteres
/**
 * Función visitante que se encarga de buscar coincidencias con el prefijo pasado y las palabras del árbol correcto.
 */
void visitante(void *dato, void *extra) {
  Palabra *p = dato;
  const char *prefijo = (const char *) extra;

  if (strncmp(p->palabra, prefijo, 3) == 0) {
    printf("%s (%u)\n", p->palabra, p->cuenta);
  }
}

/**
 * Imprime las palabras que coinciden con los 3 caracteres pasados como dato
 */
void tablahash_buscar_prefijo(TablaHash tabla, const char *prefijo) {
  assert(tabla != NULL);
  assert(prefijo != NULL);
  assert(strlen(prefijo) >= 3);

  unsigned char idx = (unsigned char) prefijo[0];
  CasillaHash *bucket = &tabla->elems[idx];

  // Si el árbol no está creado, no hay coincidencias.
  if (bucket->arbol == NULL) {
    return;
  }

  avl_recorrer(bucket->arbol, AVL_RECORRIDO_IN, visitante, (void *) prefijo);
}

// Cuenta de palabras por letra
/**
 * Devuelve la cantidad de palabras que comienzan con la letra dada.
 */
unsigned tablahash_cant_por_letra(TablaHash tabla, const char letra) {
  assert(tabla != NULL);

  unsigned char idx = (unsigned char) letra;
  CasillaHash *bucket = &tabla->elems[idx];

  return bucket->cantElems;
}

// Eliminación
/**
 * Elimina la palabra de la tabla si está, o disminuye su contador si ya estaba.
 */
void tablahash_eliminar(TablaHash tabla, const char *pal) {
  assert(tabla != NULL);
  assert(pal != NULL);

  unsigned char idx = (unsigned char) pal[0];
  CasillaHash *bucket = &tabla->elems[idx];

  // No hay árbol. La palabra no está.
  if (bucket->arbol == NULL) {
    return;
  }

  Palabra key;
  key.palabra = (char *) pal;
  key.cuenta = 0;

  Palabra *p = avl_buscar_dato(bucket->arbol, &key);

  // La palabra no está
  if (p == NULL) {
    return;
  }
  // Hay al menos una ocurrencia.
  p->cuenta--;
  bucket->cantElems--;

  // No quedan ocurrencias de la palabra. La eliminamos.
  if (p->cuenta == 0) {
    avl_eliminar(bucket->arbol, &key);
    tabla->numElems--;
  }
}
