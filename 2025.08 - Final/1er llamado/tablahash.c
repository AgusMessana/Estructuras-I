#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

typedef enum {
  LIBRE,
  BORRADA,
  OCUPADA,
} EstadoCasilla;

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
  EstadoCasilla estado;
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
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].estado = LIBRE;
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
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].estado == OCUPADA)
      tabla->destr(tabla->elems[idx].dato);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Duplica la capacidad de la tabla y rehashea los elementos.
 */
void tablahash_redimensionar(TablaHash tabla) {
  unsigned nuevaCap = tabla->capacidad * 2;
  CasillaHash *nuevoElems = malloc(sizeof(CasillaHash) * nuevaCap);
  assert(nuevoElems != NULL);

  for (unsigned i = 0; i < nuevaCap; ++i) {
    nuevoElems[i].dato = NULL;
    nuevoElems[i].estado = LIBRE;
  }

  CasillaHash *viejoElems = tabla->elems;
  unsigned viejaCap = tabla->capacidad;
  tabla->numElems = 0;

  for (unsigned i = 0; i < viejaCap; ++i) {
    if (viejoElems[i].estado == OCUPADA) {
      void *dato = viejoElems[i].dato;

      unsigned idx_inicial = tabla->hash(dato) % nuevaCap;
      int colocado = 0;
      for (unsigned j = 0; j < nuevaCap && !colocado; ++j) {
        unsigned idx = (idx_inicial + j) % nuevaCap;
        if (nuevoElems[idx].estado == LIBRE) {
          nuevoElems[idx].dato = dato;
          nuevoElems[idx].estado = OCUPADA;
          tabla->numElems++;
          colocado = 1;
        }
      }
    }
  }

  tabla->elems = nuevoElems;
  tabla->capacidad = nuevaCap;
  free(viejoElems);
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
  float limite_fdc = 0.75;
  float fdc = (float) (tabla->numElems + 1) / (float) tabla->capacidad;
  int idx_insertar = -1;
  if (fdc > limite_fdc) {
    tablahash_redimensionar(tabla);
    idx_inicial = tabla->hash(dato) % tabla->capacidad;
  }
  for (unsigned i = 0; i < tabla->capacidad; ++i) {
    unsigned idx = (idx_inicial + i) % tabla->capacidad;

    if (tabla->elems[idx].estado == OCUPADA
        && tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = tabla->copia(dato);
      return;
    }
    if (tabla->elems[idx].estado == BORRADA) {
      if (idx_insertar == -1) {
        idx_insertar = idx;
      }
    }

    if (tabla->elems[idx].estado == LIBRE) {
      int destino;
      if (idx_insertar != -1) {
        destino = idx_insertar;
      } else {
        destino = idx;
      }
      tabla->elems[destino].dato = tabla->copia(dato);
      tabla->elems[destino].estado = OCUPADA;
      tabla->numElems++;
      return;
    }
  }
  if (idx_insertar != -1) {
    tabla->elems[idx_insertar].dato = tabla->copia(dato);
    tabla->elems[idx_insertar].estado = OCUPADA;
    tabla->numElems++;
  }

  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
  for (unsigned i = 0; i < tabla->capacidad; ++i) {
    unsigned idx = (idx_inicial + i) % tabla->capacidad;
    if (tabla->elems[idx].estado == OCUPADA
        && tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      return tabla->elems[idx].dato;
    }
    if (tabla->elems[idx].estado == LIBRE) {
      return NULL;
    }
  }

  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
  for (unsigned i = 0; i < tabla->capacidad; ++i) {
    unsigned idx = (idx_inicial + i) % tabla->capacidad;
    if (tabla->elems[idx].estado == OCUPADA
        && tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = NULL;
      tabla->elems[idx].estado = BORRADA;
      tabla->numElems--;
      return;
    }
    if (tabla->elems[idx].estado == LIBRE) {
      return;
    }
  }
}
