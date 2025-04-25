#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);

// Retorna un entero negativo si el primer argumento es menor que el segundo, 0 si son iguales, y un entero positivo en caso contrario.
typedef int (*FuncionComparadora)(void *, void *);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef GList SGList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

// Devuelve una nueva lista con los elementos que cumplen con el predicado
GList glist_filtrar(GList lista, Predicado pred, FuncionCopia copy);

// Listas generales ordenadas
// Retorna una lista ordenada vacía
SGList sglist_crear();

// Destruye una lista ordenada
void sglist_destruir(SGList lista, FuncionDestructora dest);

// Determina si una lista ordenada es vacía
int sglist_vacia(SGList lista);

// Inserta un nuevo dato en la lista ordenada
// La funcion de comparación es la que determina el criterio de ordenación

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copy,
                       FuncionComparadora comp);

// Busca un dato en una lista ordenada.
// Devuelve 1 si lo encuntra y 0 si no.
int sglist_buscar(GList lista, void *dato, FuncionComparadora comp);

// Construye una lista ordenada a partir de un arreglo de elementos y su longitud.
SGList sglist_arr(void **arreglo, int longi, FuncionCopia copy,
                  FuncionComparadora comp);

//! Funciones auxiliares para ejercicio P3.2
// Devuelve el primer elemento de la lista
void* glist_primero(GList lista);

// Elimina el primer elemento de la lista
GList glist_eliminar_primero(GList lista, FuncionDestructora destroy);

#endif                          /* __GLIST_H__ */
