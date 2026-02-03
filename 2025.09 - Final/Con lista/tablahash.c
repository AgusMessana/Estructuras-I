#include "tablahash.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  GList lista;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned capacidad;
  unsigned numElems;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una Tabla Hash con la capacidad y funciones dadas.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora dest,
                          FuncionHash hash) {
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems);
  tabla->capacidad = capacidad;
  tabla->numElems = 0;
  tabla->comp = comp;
  tabla->copia = copia;
  tabla->destr = dest;
  tabla->hash = hash;
  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    tabla->elems[idx].lista = glist_crear();
  }

  return tabla;
}

/**
 * Destrutye una Tabla Hash.
 */
void tablahash_destruir(TablaHash tabla) {
  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    glist_destruir(tabla->elems[idx].lista, tabla->destr);
  }

  free(tabla->elems);
  free(tabla);
}

/**
 * Devuelve el elemento buscado si está en la tabla o NULL si no está.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  for (GList aux = tabla->elems[idx].lista; aux != NULL; aux = aux->next) {
    if (tabla->comp(dato, aux->data) == 0) {
      return aux->data;
    }
  }

  return NULL;
}

/**
 * Inserta un elemento en la Tabla Hash.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  if (glist_esta(tabla->elems[idx].lista, dato, tabla->comp) == 1) {
    tabla->elems[idx].lista =
        glist_eliminar(tabla->elems[idx].lista, dato, tabla->comp,
                       tabla->destr);
  } else {
    tabla->numElems++;
  }
  tabla->elems[idx].lista =
      glist_agregar_inicio(tabla->elems[idx].lista, dato, tabla->copia);
}

/**
 * Elimina un elemento dado de la tabla si está, y no hace nada si no está
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  if (glist_esta(tabla->elems[idx].lista, dato, tabla->comp) == 1) {
    tabla->elems[idx].lista =
        glist_eliminar(tabla->elems[idx].lista, dato, tabla->comp,
                       tabla->destr);
    tabla->numElems--;
  }
}

/**
 * Devuelve la cantidad de elementos de la tabla.
 */
unsigned tablahash_numElems(TablaHash tabla) {
  return tabla->numElems;
}

/**
 * Devuelve la capacidad de la tabla.
 */
unsigned tablahash_capacidad(TablaHash tabla) {
  return tabla->capacidad;
}

/**
 * Determina si una tabla necesita rehash
 */
static int necesita_rehash(TablaHash tabla) {
  return (tabla->numElems * 4 > tabla->capacidad * 3);
}

/**
 * Hace rehash a la tabla dada.
 */
static void rehash(TablaHash tabla, unsigned nuevaCap) {
  CasillaHash *nuevoElems = malloc(sizeof(CasillaHash) * nuevaCap);
  assert(nuevoElems);

  for (unsigned idx = 0; idx < nuevaCap; idx++) {
    nuevoElems[idx].lista = glist_crear();
  }

  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    for (GList nodo = tabla->elems[idx].lista; nodo != NULL; nodo = nodo->next) {
      void *dato = nodo->data;
      unsigned idx_nuevo = tabla->hash(dato) % nuevaCap;
      nuevoElems[idx_nuevo].lista =
          glist_agregar_inicio(nuevoElems[idx_nuevo].lista, dato, tabla->copia);
    }
  }

  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    glist_destruir(tabla->elems[idx].lista, tabla->destr);
  }
  free(tabla->elems);

  tabla->elems = nuevoElems;
  tabla->capacidad = nuevaCap;
}

/**
 * Inserta un elemento en la Tabla Hash y hace rehash de ser necesario.
 */
void tablahash_insertar_balance(TablaHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  if (glist_esta(tabla->elems[idx].lista, dato, tabla->comp) == 1) {
    tabla->elems[idx].lista =
        glist_eliminar(tabla->elems[idx].lista, dato, tabla->comp,
                       tabla->destr);
  } else {
    tabla->numElems++;
  }
  tabla->elems[idx].lista =
      glist_agregar_inicio(tabla->elems[idx].lista, dato, tabla->copia);

  if (necesita_rehash(tabla) == 1) {
    rehash(tabla, tabla->capacidad * 2);
  }
}
