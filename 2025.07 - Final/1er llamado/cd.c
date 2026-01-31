#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cd.h"

/**
 * Crea un conjunto difuso
 */
CD cd_crear() {
  return NULL;
}

/**
 * Elimina un elemento del conjunto.
 */
static CD cd_eliminar(CD conj, void *dato, FuncionComparadora comp,
                      FuncionDestructora dest) {
  assert(comp != NULL);
  assert(dest != NULL);
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
 * Toma un CD, un elemento de tipo void* y un grado de pertenencia de tipo double y modifiqua el grado de pertenencia del elemento.
 * Si el nuevo grado de pertenencia es 0 el elemento debe ser eliminado.
 */
CD cd_modificar_gp(CD conj, void *dato, double gp, FuncionComparadora comp,
                   FuncionDestructora dest) {
  if (conj == NULL || gp < 0 || gp > 1) {
    return conj;
  }

  for (CD aux = conj; aux != NULL; aux = aux->sig) {
    if (comp(dato, aux->dato) == 0) {
      if (gp == 0.0) {
        conj = cd_eliminar(conj, dato, comp, dest);
        return conj;
      }
      aux->gp = gp;
      return conj;
    }
  }

  return conj;
}

/**
 * Agrega un elemento al inicio del conjunto
 */
static CD cd_agregar_inicio(CD conj, void *dato, double gp,
                            FuncionCopiadora copy) {
  CDNodo *nuevoNodo = malloc(sizeof(CDNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->sig = conj;
  nuevoNodo->gp = gp;
  nuevoNodo->dato = copy(dato);
  return nuevoNodo;
}

/**
 * Tome un CD, un elemento de tipo void* y un grado de pertenencia de tipo double y agregua el elemento al conjunto con el grado de pertenencia dado.
 */
CD cd_agregar(CD conj, void *dato, double gp, FuncionCopiadora copy,
              FuncionComparadora comp, FuncionDestructora dest) {
  assert(copy != NULL && comp != NULL && dest != NULL);
  if (gp < 0 || gp > 1) {
    return conj;
  }
  for (CD aux = conj; aux != NULL; aux = aux->sig) {
    if (comp(dato, aux->dato) == 0) {
      conj = cd_modificar_gp(conj, dato, gp, comp, dest);
      return conj;
    }
  }

  if (gp != 0) {
    conj = cd_agregar_inicio(conj, dato, gp, copy);
  }
  return conj;
}

/**
 * Toma dos conjuntos difusos A y B y devuelva un int indicando si A es subconjunto de B.
 */
int cd_subconjunto(CD A, CD B, FuncionComparadora comp) {
  assert(comp != NULL);
  if (A == NULL) {
    return 1;
  }

  for (CD aux1 = A; aux1 != NULL; aux1 = aux1->sig) {
    int encontrado = 0;
    for (CD aux2 = B; aux2 != NULL && encontrado != 1; aux2 = aux2->sig) {
      if (comp(aux1->dato, aux2->dato) == 0) {
        if (aux1->gp > aux2->gp) {
          return 0;
        }
        encontrado = 1;
      }
    }
    if (encontrado == 0) {
      return 0;
    }
  }

  return 1;
}

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la unión de ambos
 */
CD cd_union(CD A, CD B, FuncionComparadora comp, FuncionCopiadora copy,
            FuncionDestructora dest) {
  assert(comp != NULL && copy != NULL && dest != NULL);
  CD uni = cd_crear();
  for (CD aux1 = A; aux1 != NULL; aux1 = aux1->sig) {
    uni = cd_agregar(uni, aux1->dato, aux1->gp, copy, comp, dest);
  }

  for (CD aux1 = B; aux1 != NULL; aux1 = aux1->sig) {
    int encontrado = 0;
    for (CD aux2 = uni; aux2 != NULL && encontrado != 1; aux2 = aux2->sig) {
      if (comp(aux1->dato, aux2->dato) == 0) {
        if (aux1->gp > aux2->gp) {
          uni = cd_modificar_gp(uni, aux1->dato, aux1->gp, comp, dest);
        }

        encontrado = 1;
      }
    }
    if (encontrado == 0) {
      uni = cd_agregar(uni, aux1->dato, aux1->gp, copy, comp, dest);
    }
  }

  return uni;
}

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la diferencia entre ambos.
 */
CD cd_diferencia(CD A, CD B, FuncionComparadora comp, FuncionCopiadora copy,
                 FuncionDestructora dest) {
  assert(comp != NULL && copy != NULL && dest != NULL);
  CD dif = cd_crear();
  for (CD aux1 = A; aux1 != NULL; aux1 = aux1->sig) {
    int encontrado = 0;
    for (CD aux2 = B; aux2 != NULL && encontrado != 1; aux2 = aux2->sig) {
      if (comp(aux1->dato, aux2->dato) == 0) {
        if (aux1->gp > aux2->gp) {
          double gp_dif = aux1->gp - aux2->gp;
          dif = cd_agregar(dif, aux1->dato, gp_dif, copy, comp, dest);
          encontrado = 1;
        }
        encontrado = 1;
      }
    }
    if (encontrado == 0) {
      dif = cd_agregar(dif, aux1->dato, aux1->gp, copy, comp, dest);
    }
  }

  return dif;
}
