#ifndef __1ER_PARCIAL_2024_H__
#define __1ER_PARCIAL_2024_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparar)(void *dato1, void *dato2);
typedef int (*Predicado)(void *dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef struct _GNode *GList;

// Devuelve una lista vacía
GList glista_crear();

// Destrucción de la lista
void glist_destruir(GList list, FuncionDestructora dest);

// Determina si la lista está vacía
int glist_vacia(GList list);

// Agrega un elemento al inicio de la lista
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy);

// Busca un elemento en la lista
int glist_buscar(GList list, void *data, FuncionComparar comp);

// Recorrido de la lista usando la función pasada
void glist_recorrer(GList list, FuncionVisitante visit);

// Dada una lista, retorna una nueva lista con los elementos que cumplen con el predicado
GList glist_filtrar(GList list, Predicado p, FuncionCopia copy);

typedef void **GArray;

typedef struct {
  char *nombre, *direccion, *dni;
  int edad;
} Persona;

// Vuelca los datos de la lista recibida en un arreglo tipo GArray. El arreglo debe ser redimensionable, adaptándose a la cantidad de elementos que posee la lista
GArray listToArray(GList lista, FuncionCopia c);

// Toma una lista de estructuras Persona y devuelve un arreglo con los elementos de la lista reutilizando las estructuras
GArray listToArrayPersona(GList lista);

// Dada una lista con elementos de tipo Persona, utilize la función glist_filtrar y devuelva una nueva lista con aquellos elementos cuya edad sea mayor a 18 años y tales que en su dirección hay al menos una letra 'a', ya sea mayúscula o minúscula
GList mayores18ConA(GList lista);

#endif
