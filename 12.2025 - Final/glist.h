#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

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
 * Devuelve 1 si el elemento está en la lista, y 0 si no está.
 */
int glist_esta(GList lista, void *dato, FuncionComparadora comp);

/**
 * Devuelve el dato pasado si está y NULL en caso contrario
 */
void *glist_dato_esta(GList lista, void *dato, FuncionComparadora comp);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopiadora copiar);

/**
 * Elimina el elemento pasado de la lista.
 */
GList glist_eliminar(GList lista, void *dato, FuncionComparadora comp,
                     FuncionDestructora destr);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

#endif                          /* __GLIST_H__ */
