#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Enumeración para saber si eliminamos un dato, si está la casilla ocupada o si está libre.
 */
typedef enum {
  LIBRE,                        // nunca se usó
  OCUPADA,                      // tiene dato válido
  BORRADA                       // tuvo un dato, pero se eliminó
} EstadoCasilla;

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
  EstadoCasilla estado;
} Casilla;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  Casilla *elems;
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
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);

  tabla->elems = malloc(sizeof(Casilla) * capacidad);
  assert(tabla->elems != NULL);

  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

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
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    if (tabla->elems[idx].estado == OCUPADA) {
      tabla->destr(tabla->elems[idx].dato);
    }
  }

  free(tabla->elems);
  free(tabla);
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
  int idx_insertar = -1;

  for (int i = 0; i < tabla->capacidad; ++i) {
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
      if (idx_insertar != -1) {
        tabla->elems[idx_insertar].dato = tabla->copia(dato);
        tabla->elems[idx_insertar].estado = OCUPADA;
        tabla->numElems++;
        return;
      } else {
        tabla->elems[idx].dato = tabla->copia(dato);
        tabla->elems[idx].estado = OCUPADA;
        tabla->numElems++;
        return;
      }
    }
  }
  if (idx_insertar != -1) {
    tabla->elems[idx_insertar].dato = tabla->copia(dato);
    tabla->elems[idx_insertar].estado = OCUPADA;
    tabla->numElems++;
    return;
  }
  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;

  for (int i = 0; i < tabla->capacidad; ++i) {
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
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;

  for (int i = 0; i < tabla->capacidad; ++i) {
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

  return;
}

int tablahash_posicion(TablaHash tabla, void *dato) {
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;

  for (int i = 0; i < (int) tabla->capacidad; ++i) {
    unsigned idx = (idx_inicial + i) % tabla->capacidad;

    // Si la casilla está ocupada, puede ser el dato que buscamos
    if (tabla->elems[idx].estado == OCUPADA &&
        tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      return (int) idx;
    }
    // Si encontramos una casilla nunca usada, ya sabemos que el dato no está
    if (tabla->elems[idx].estado == LIBRE) {
      return -1;
    }
    // Si está BORRADA o OCUPADA con otra clave, seguimos
  }

  // Dimos toda la vuelta y no lo encontramos
  return -1;
}
