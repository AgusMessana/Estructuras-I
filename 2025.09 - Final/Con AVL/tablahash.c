#include "tablahash.h"
#include "avl.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  AVL arbol;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].arbol = avl_crear(copia, comp, destr);
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) {
  return tabla->numElems;
}

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) {
  return tabla->capacidad;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    avl_destruir(tabla->elems[idx].arbol);
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

struct _ctx_rehash {
  CasillaHash *nuevoElems;
  unsigned nuevaCap;
  FuncionHash hash;
};

static void visitante_rehash(void *dato, void *extra) {
  struct _ctx_rehash *ctx = extra;
  unsigned idx = ctx->hash(dato) % ctx->nuevaCap;
  avl_insertar(ctx->nuevoElems[idx].arbol, dato);
}

/**
 * Rehashea la tabla, aumentando además la capacidad al doble.
 */
void tablahash_rehash(TablaHash tabla) {
  unsigned nuevaCap = tabla->capacidad * 2;
  CasillaHash *nuevoElems = malloc(sizeof(CasillaHash) * nuevaCap);
  assert(nuevoElems != NULL);
  for (unsigned i = 0; i < nuevaCap; ++i) {
    nuevoElems[i].arbol = avl_crear(tabla->copia, tabla->comp, tabla->destr);
    assert(nuevoElems[i].arbol != NULL);
  }
  struct _ctx_rehash ctx;
  ctx.nuevoElems = nuevoElems;
  ctx.nuevaCap = nuevaCap;
  ctx.hash = tabla->hash;
  for (unsigned i = 0; i < tabla->capacidad; ++i) {
    avl_recorrer(tabla->elems[i].arbol, AVL_RECORRIDO_IN, visitante_rehash,
                 &ctx);
  }
  for (unsigned i = 0; i < tabla->capacidad; ++i) {
    avl_destruir(tabla->elems[i].arbol);
  }
  free(tabla->elems);
  tabla->elems = nuevoElems;
  tabla->capacidad = nuevaCap;
}

/**
 * Inserta un dato en la tabla.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  float limite_fdc = 0.7;
  float fdc = (float) (tabla->numElems + 1) / (float) tabla->capacidad;
  if (fdc > limite_fdc) {
    tablahash_rehash(tabla);
    idx = tabla->hash(dato) % tabla->capacidad;
  }
  if (avl_buscar(tabla->elems[idx].arbol, dato) == 0) {
    avl_insertar(tabla->elems[idx].arbol, dato);
    tabla->numElems++;
  }
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  if (avl_buscar(tabla->elems[idx].arbol, dato) == 1) {
    avl_eliminar(tabla->elems[idx].arbol, dato);
    tabla->numElems--;
  }
}

int tablahash_contiene(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  return avl_buscar(tabla->elems[idx].arbol, dato) != 0;
}
