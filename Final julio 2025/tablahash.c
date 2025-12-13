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

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].lista = NULL;
  }

  return tabla;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {
  assert(tabla != NULL);

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    glist_destruir(tabla->elems[idx].lista, tabla->destr);
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  assert(tabla != NULL);
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  GList nodo = tabla->elems[idx].lista;
  while (nodo != NULL && tabla->comp(nodo->data, dato) != 0) {
    nodo = nodo->next;
  }
  if (nodo == NULL) {
    tabla->elems[idx].lista =
        glist_agregar_inicio(tabla->elems[idx].lista, dato, tabla->copia);
    tabla->numElems++;
  } else {
    tabla->destr(nodo->data);
    nodo->data = tabla->copia(dato);
  }
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  assert(tabla != NULL);
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  if (tabla->elems[idx].lista == NULL) {
    return NULL;
  }
  GList nodo = tabla->elems[idx].lista;
  while (nodo != NULL) {
    if (tabla->comp(nodo->data, dato) == 0) {
      return nodo->data;
    }
    nodo = nodo->next;
  }

  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {
  assert(tabla != NULL);
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  if (tablahash_buscar(tabla, dato) == NULL) {
    return;
  }

  tabla->elems[idx].lista =
      glist_eliminar(tabla->elems[idx].lista, dato, tabla->destr, tabla->comp);
  tabla->numElems--;
}

/**
 * Devuelve 1 si la matriz es simétrica, y 0 si no lo es.
 */
int es_simetrica(TablaHash * filas, unsigned n) {
  for (unsigned i = 0; i < n; ++i) {
    for (unsigned j = 0; j < filas[i]->capacidad; ++j) {
      for (GList nodo = filas[i]->elems[j].lista; nodo != NULL;
           nodo = nodo->next) {
        unsigned k = *(unsigned *) nodo->data;
        unsigned key = i;
        if (tablahash_buscar(filas[k], &key) == NULL) {
          return 0;
        }
      }
    }
  }

  return 1;
}
