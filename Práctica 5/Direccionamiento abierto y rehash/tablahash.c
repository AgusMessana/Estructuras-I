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
 * Duplica la capacidad de la tabla y reposicione todos los elementos de acuerdo a la nueva posición que le asigne la función de hash.
 */
void tablahash_redimensionar(TablaHash tabla) {
  Casilla *viejoElems = tabla->elems;
  unsigned viejaCap = tabla->capacidad;

  unsigned nuevaCap = viejaCap * 2;
  Casilla *nuevoElems = malloc(sizeof(Casilla) * nuevaCap);
  assert(nuevoElems != NULL);
  for (unsigned i = 0; i < nuevaCap; ++i) {
    nuevoElems[i].dato = NULL;
    nuevoElems[i].estado = LIBRE;
  }
  tabla->elems = nuevoElems;
  tabla->capacidad = nuevaCap;
  tabla->numElems = 0;

  for (unsigned i = 0; i < viejaCap; ++i) {
    if (viejoElems[i].estado == OCUPADA) {
      void *dato = viejoElems[i].dato;

      unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
      int colocado = 0;

      for (unsigned j = 0; j < tabla->capacidad && !colocado; ++j) {
        unsigned idx = (idx_inicial + j) % tabla->capacidad;
        if (tabla->elems[idx].estado == LIBRE) {
          tabla->elems[idx].dato = dato;
          tabla->elems[idx].estado = OCUPADA;
          tabla->numElems++;
          colocado = 1;
        }
      }
    }
  }
  free(viejoElems);
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  float limite_fdc = 0.7f;
  unsigned idx_inicial = tabla->hash(dato) % tabla->capacidad;
  int idx_insertar = -1;

  for (int i = 0; i < (int) tabla->capacidad; ++i) {

    unsigned idx = (idx_inicial + i) % tabla->capacidad;

    /* CASO 1: la clave ya existe → reemplazo */
    if (tabla->elems[idx].estado == OCUPADA
        && tabla->comp(tabla->elems[idx].dato, dato) == 0) {

      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = tabla->copia(dato);
      return;
    }

    /* CASO 2: casilla BORRADA → posible lugar para insertar */
    if (tabla->elems[idx].estado == BORRADA) {
      if (idx_insertar == -1) {
        idx_insertar = idx;
      }
    }

    /* CASO 3: casilla LIBRE → inserción nueva */
    if (tabla->elems[idx].estado == LIBRE) {

      /* Elegir destino sin usar operador ternario */
      int destino;
      if (idx_insertar != -1) {
        destino = idx_insertar;
      } else {
        destino = idx;
      }

      /* Calcular factor de carga recién ahora */
      float fdc = (float) (tabla->numElems + 1) / (float) tabla->capacidad;
      if (fdc >= limite_fdc) {

        /* Rehash y reinserción */
        tablahash_redimensionar(tabla);
        tablahash_insertar(tabla, dato);
        return;
      }

      /* Insertar normalmente */
      tabla->elems[destino].dato = tabla->copia(dato);
      tabla->elems[destino].estado = OCUPADA;
      tabla->numElems++;
      return;
    }
  }

  /* CASO FINAL: no hubo LIBRE pero sí BORRADA */
  if (idx_insertar != -1) {

    float fdc = (float) (tabla->numElems + 1) / (float) tabla->capacidad;
    if (fdc >= limite_fdc) {
      tablahash_redimensionar(tabla);
      tablahash_insertar(tabla, dato);
      return;
    }

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
