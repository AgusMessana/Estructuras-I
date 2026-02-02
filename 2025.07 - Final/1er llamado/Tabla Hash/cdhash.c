#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cdhash.h"

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  CD conj;
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
  FuncionDestructora dest;
  FuncionHash hash;
};

/**
 * Crea un conjunto difuso
 */
TablaHash cd_crear(unsigned capacidad, FuncionComparadora comp,
                   FuncionCopiadora copy, FuncionDestructora dest,
                   FuncionHash hash) {
  assert(capacidad > 0);
  assert(comp != NULL && copy != NULL && dest != NULL && hash != NULL);

  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  if (tabla->elems == NULL) {
    free(tabla);
    return NULL;
  }

  tabla->capacidad = capacidad;
  tabla->numElems = 0;
  tabla->comp = comp;
  tabla->copia = copy;
  tabla->dest = dest;
  tabla->hash = hash;
  for (unsigned idx = 0; idx < tabla->capacidad; idx++) {
    tabla->elems[idx].conj = NULL;
  }

  return tabla;
}

/**
 * Agrega un elemento al inicio del conjunto
 */
static CD cd_agregar_inicio(CD conj, void *dato, double gp,
                            FuncionCopiadora copy) {
  assert(dato != NULL);
  assert(copy != NULL);
  CDNodo *nuevoNodo = malloc(sizeof(CDNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->sig = conj;
  nuevoNodo->gp = gp;
  nuevoNodo->dato = copy(dato);
  return nuevoNodo;
}

/**
 * Toma una tabla, un elemento de tipo void* y un grado de pertenencia de tipo double y agregua el elemento al conjunto con el grado de pertenencia dado.
 * Si el elemento ya se encontraba en el conjunto, no se modifica su grado de pertenencia ni se agrega nuevamente.
 * Si el grado de pertenencia es 0, no se agrega.
 */
TablaHash cd_agregar(TablaHash tabla, void *dato, double gp) {
  assert(tabla != NULL);
  assert(dato != NULL);
  assert(tabla->comp != NULL && tabla->copia != NULL && tabla->hash != NULL);
  assert(tabla->capacidad > 0);
  if (gp <= 0.0 || gp > 1.0) {
    return tabla;
  }

  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  for (CD aux1 = tabla->elems[idx].conj; aux1 != NULL; aux1 = aux1->sig) {
    if (tabla->comp(aux1->dato, dato) == 0) {
      return tabla;
    }
  }

  tabla->elems[idx].conj =
      cd_agregar_inicio(tabla->elems[idx].conj, dato, gp, tabla->copia);
  tabla->numElems++;

  return tabla;
}

/**
 * Elimina un elemento del conjunto.
 */
static CD cd_eliminar(CD conj, void *dato, FuncionComparadora comp,
                      FuncionDestructora dest) {
  assert(dato != NULL);
  assert(comp != NULL && dest != NULL);

  CD actual = conj;
  CD ant = NULL;
  while (actual != NULL && comp(actual->dato, dato) != 0) {
    ant = actual;
    actual = actual->sig;
  }

  if (actual == NULL) {
    return conj;
  }
  if (ant == NULL) {
    CD nuevo = actual->sig;
    dest(actual->dato);
    free(actual);
    return nuevo;
  }

  ant->sig = actual->sig;
  dest(actual->dato);
  free(actual);
  return conj;
}

/**
 * Toma una tabla, un elemento de tipo void* y un grado de pertenencia de tipo double y modifica el grado de pertenencia del elemento.
 * Si el nuevo grado de pertenencia es 0 el elemento debe ser eliminado.
 * Si el elemento no estaba en la tabla, no se modifica nada.
 */
TablaHash cd_modificar_gp(TablaHash tabla, void *dato, double gp) {
  assert(tabla != NULL);
  assert(dato != NULL);
  assert(tabla->comp != NULL && tabla->dest != NULL && tabla->hash != NULL);
  assert(tabla->capacidad > 0);
  if (gp < 0.0 || gp > 1.0) {
    return tabla;
  }

  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  for (CD aux1 = tabla->elems[idx].conj; aux1 != NULL; aux1 = aux1->sig) {
    if (tabla->comp(aux1->dato, dato) == 0) {
      if (gp == 0.0) {
        tabla->elems[idx].conj =
            cd_eliminar(tabla->elems[idx].conj, dato, tabla->comp, tabla->dest);
        tabla->numElems--;
      } else {
        aux1->gp = gp;
      }

      return tabla;
    }
  }

  return tabla;
}

/**
 * Devuelve el gp de un dato o 0 si el dato no está en la tabla. 
 */
static double cd_buscar_gp(TablaHash tabla, void *dato) {
  assert(tabla != NULL);
  assert(tabla->comp != NULL && tabla->hash != NULL);
  assert(tabla->capacidad > 0);
  assert(dato != NULL);

  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  for (CD aux1 = tabla->elems[idx].conj; aux1 != NULL; aux1 = aux1->sig) {
    if (tabla->comp(aux1->dato, dato) == 0) {
      return aux1->gp;
    }
  }

  return 0.0;
}

/**
 * Toma dos conjuntos difusos A y B y devuelva un int indicando si A es subconjunto de B.
 */
int cd_subconjunto(TablaHash A, TablaHash B) {
  assert(A != NULL && B != NULL);
  assert(A->comp != NULL && B->comp != NULL && A->hash != NULL
         && B->hash != NULL);
  assert(A->capacidad > 0 && B->capacidad > 0);

  for (unsigned i = 0; i < A->capacidad; i++) {
    for (CD aux1 = A->elems[i].conj; aux1 != NULL; aux1 = aux1->sig) {
      double gpA = aux1->gp;
      double gpB = cd_buscar_gp(B, aux1->dato);

      if (gpA > gpB) {
        return 0;
      }
    }
  }

  return 1;
}

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la unión de ambos
 */
TablaHash cd_union(TablaHash A, TablaHash B) {
  assert(A != NULL && B != NULL);
  assert(A->comp != NULL && B->comp != NULL && A->copia != NULL
         && B->copia != NULL && A->dest != NULL && B->dest != NULL
         && A->hash != NULL && B->hash != NULL);
  assert(A->capacidad > 0 && B->capacidad > 0);

  unsigned capU;
  if (A->capacidad > B->capacidad) {
    capU = A->capacidad;
  } else {
    capU = B->capacidad;
  }
  TablaHash tablaUnion = cd_crear(capU, A->comp, A->copia, A->dest, A->hash);

  for (unsigned i = 0; i < A->capacidad; i++) {
    for (CD aux1 = A->elems[i].conj; aux1 != NULL; aux1 = aux1->sig) {
      tablaUnion = cd_agregar(tablaUnion, aux1->dato, aux1->gp);
    }
  }

  for (unsigned i = 0; i < B->capacidad; i++) {
    for (CD aux2 = B->elems[i].conj; aux2 != NULL; aux2 = aux2->sig) {
      double gpU = cd_buscar_gp(tablaUnion, aux2->dato);

      if (gpU == 0.0) {
        tablaUnion = cd_agregar(tablaUnion, aux2->dato, aux2->gp);
      } else if (aux2->gp > gpU) {
        tablaUnion = cd_modificar_gp(tablaUnion, aux2->dato, aux2->gp);
      }
    }
  }

  return tablaUnion;
}

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la diferencia entre ambos.
 */
TablaHash cd_diferencia(TablaHash A, TablaHash B) {
  assert(A != NULL && B != NULL);
  assert(A->comp != NULL && B->comp != NULL && A->copia != NULL
         && B->copia != NULL && A->dest != NULL && B->dest != NULL
         && A->hash != NULL && B->hash != NULL);
  assert(A->capacidad > 0 && B->capacidad > 0);

  unsigned capD;
  if (A->capacidad > B->capacidad) {
    capD = A->capacidad;
  } else {
    capD = B->capacidad;
  }
  TablaHash tablaDif = cd_crear(capD, A->comp, A->copia, A->dest, A->hash);

  for (unsigned i = 0; i < A->capacidad; i++) {
    for (CD aux1 = A->elems[i].conj; aux1 != NULL; aux1 = aux1->sig) {
      double gpB = cd_buscar_gp(B, aux1->dato);
      if (aux1->gp > gpB) {
        tablaDif = cd_agregar(tablaDif, aux1->dato, aux1->gp - gpB);
      }
    }
  }

  return tablaDif;
}
