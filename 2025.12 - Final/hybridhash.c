#include "hybridhash.h"
#include "avl.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  AVL arbol;
  GList lista;
  unsigned convertido;
  unsigned cantElems;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _HybridHash {
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
HybridHash hybrid_hash_crear(unsigned capacidad, FuncionCopiadora copia,
                             FuncionComparadora comp, FuncionDestructora destr,
                             FuncionHash hash) {
  HybridHash tabla = malloc(sizeof(struct _HybridHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->capacidad = capacidad;
  tabla->numElems = 0;
  tabla->comp = comp;
  tabla->copia = copia;
  tabla->destr = destr;
  tabla->hash = hash;

  for (unsigned idx = 0; idx < capacidad; idx++) {
    tabla->elems[idx].arbol = avl_crear(copia, comp, destr);
    tabla->elems[idx].lista = glist_crear();
    tabla->elems[idx].convertido = 0;
    tabla->elems[idx].cantElems = 0;
  }

  return tabla;
}

static void glist_a_AVL(GList lista, AVL arbol) {
  GList nodo = lista;
  while (nodo != NULL) {
    avl_insertar(arbol, nodo->data);
    nodo = nodo->next;
  }
}

/**
 * Inserta un elemento en la tabla. Si al agregar se supera el umbral, se cambia de lista a árbol. Si no, no se hace el cambio.
 * Si el elemento está repetdio, no se agrega.
 */
void hybrid_hash_insertar(HybridHash tabla, void *dato) {
  unsigned T = 10;
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Caso 1: en la casilla se usa un AVL
  if (tabla->elems[idx].convertido == 1) {
    // Chequeo que el dato no esté, para saber si incremento elementos o no
    if (avl_buscar(tabla->elems[idx].arbol, dato) == 0) {
      avl_insertar(tabla->elems[idx].arbol, dato);
      tabla->elems[idx].cantElems++;
      tabla->numElems++;
    }
  }
  // Caso 2: en la casilla hay una lista
  else if (tabla->elems[idx].convertido == 0) {
    // Chequeo si el dato ya está en la lista
    int esta = glist_esta(tabla->elems[idx].lista, dato, tabla->comp);

    // Subcaso 1: si el dato no está y al agregarlo no supero T, no migro a AVL
    if (esta == 0) {
      if (tabla->elems[idx].cantElems + 1 < T) {
        tabla->elems[idx].lista =
            glist_agregar_inicio(tabla->elems[idx].lista, dato, tabla->copia);
        tabla->elems[idx].cantElems++;
        tabla->numElems++;
      } else {                  // Subcaso 2: supero T al agregar. Migro a un AVL
        glist_a_AVL(tabla->elems[idx].lista, tabla->elems[idx].arbol);
        avl_insertar(tabla->elems[idx].arbol, dato);
        glist_destruir(tabla->elems[idx].lista, tabla->destr);
        tabla->elems[idx].lista = glist_crear();
        tabla->elems[idx].convertido = 1;
        tabla->elems[idx].cantElems++;
        tabla->numElems++;
      }
    }
  }
}

/**
 * Busca en la tabla un dato que coincida con el dato dado, y retorna el dato encontrado o NULL en caso de no hallarse en la tabla.
 */
void *hybrid_hash_buscar(HybridHash tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Caso 1: en la casilla usamos un AVL
  if (tabla->elems[idx].convertido == 1) {
    return avl_buscar_dato(tabla->elems[idx].arbol, dato);
  } else {                      // Caso 2: en la casilla hay una lista
    return glist_dato_esta(tabla->elems[idx].lista, dato, tabla->comp);
  }
}

typedef struct {
  GList *plista;
  FuncionCopiadora copy;
} ExtraAVLaLista;

static void AVL_a_glist(void *dato, void *extra) {
  ExtraAVLaLista *e = extra;
  *(e->plista) = glist_agregar_inicio(*(e->plista), dato, e->copy);
}

/**
 * Elimina un elemento en la tabla. Si al eliminar se baja del umbral, se cambia de árbol a lista. Si no, no se hace el cambio.
 */
void hybrid_hash_eliminar(HybridHash tabla, void *dato) {
  unsigned T = 10;
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Caso 1: en la casilla hay una lista
  if (tabla->elems[idx].convertido == 0) {
    // Chequeo que el dato esté, para saber si decremento elementos o no
    if (glist_esta(tabla->elems[idx].lista, dato, tabla->comp) == 1) {
      tabla->elems[idx].lista =
          glist_eliminar(tabla->elems[idx].lista, dato, tabla->comp,
                         tabla->destr);
      tabla->elems[idx].cantElems--;
      tabla->numElems--;
    }
  }
  // Caso 2: en la casilla hay un árbol
  else if (tabla->elems[idx].convertido == 1) {

    // Chequeo si el dato ya está en el AVL
    int esta = avl_buscar(tabla->elems[idx].arbol, dato);

    // Subcaso 1: si el dato está y al eliminarlo no bajo de T/2, no migro a lista
    if (esta == 1) {
      if (tabla->elems[idx].cantElems - 1 >= T / 2) {
        avl_eliminar(tabla->elems[idx].arbol, dato);
        tabla->elems[idx].cantElems--;
        tabla->numElems--;
      } else {                  // Subcaso 2: si el dato está y al eliminarlo bajo de T/2, migro a lista
        avl_eliminar(tabla->elems[idx].arbol, dato);
        tabla->elems[idx].cantElems--;
        tabla->numElems--;
        tabla->elems[idx].lista = glist_crear();

        ExtraAVLaLista e;
        e.plista = &tabla->elems[idx].lista;
        e.copy = tabla->copia;

        avl_recorrer(tabla->elems[idx].arbol, AVL_RECORRIDO_IN, AVL_a_glist,
                     &e);

        // destruir AVL (nodos + datos originales)
        avl_destruir(tabla->elems[idx].arbol);

        tabla->elems[idx].arbol =
            avl_crear(tabla->copia, tabla->comp, tabla->destr);
        tabla->elems[idx].convertido = 0;
      }
    }
  }
}
