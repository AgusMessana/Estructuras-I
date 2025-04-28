#ifndef __2DO_PARCIAL_2023_H__
#define __2DO_PARCIAL_2023_H__

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef struct {
  GNodo *primero;
  GNodo *ultimo;
} GList;

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef void *(*FuncionTransformar)(void *dato);

GList glist_crear();

GList glist_agregar_final(GList lista, void *dato, FuncionCopia copia);

void glist_destruir(GList lista, FuncionDestructora destroy);

void glist_recorrer(GList lista, FuncionVisitante visit);

// Devuelve el resultado de realizar un map a la lista, es decir, que aplique la función f a cada uno de los elementos de la misma.
GList glist_map(GList lista, FuncionTransformar f, FuncionCopia c);

// Toma un string y devuelve un nuevo string igual al anterior pero con todos sus caracteres alfabéticos en mayúscula.
void *stringMayuscula(void *dato);

#endif
