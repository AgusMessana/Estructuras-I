#ifndef __CDHASH_H__
#define __CDHASH_H__
/**
 * Funciones para manipular datos generales
 */
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionDestructora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef unsigned (*FuncionHash)(void *dato);


/**
 * Definición de la estructura
 */
typedef struct _CDNodo {
  void *dato;
  double gp;
  struct _CDNodo *sig;
} CDNodo;

typedef CDNodo *CD;
typedef struct _TablaHash *TablaHash;

/**
 * Crea un conjunto difuso
 */
TablaHash cd_crear(unsigned capacidad, FuncionComparadora comp,
                   FuncionCopiadora copy, FuncionDestructora dest,
                   FuncionHash hash);

/**
 * Toma una tabla, un elemento de tipo void* y un grado de pertenencia de tipo double y agregua el elemento al conjunto con el grado de pertenencia dado.
 * Si el elemento ya se encontraba en el conjunto, no se modifica su grado de pertenencia ni se agrega nuevamente.
 * Si el grado de pertenencia es 0, no se agrega.
 */
TablaHash cd_agregar(TablaHash tabla, void *dato, double gp);

/**
 * Toma una tabla, un elemento de tipo void* y un grado de pertenencia de tipo double y modifica el grado de pertenencia del elemento.
 * Si el nuevo grado de pertenencia es 0 el elemento debe ser eliminado.
 * Si el elemento no estaba en la tabla, no se modifica nada.
 */
TablaHash cd_modificar_gp(TablaHash tabla, void *dato, double gp);

/**
 * Toma dos conjuntos difusos A y B y devuelva un int indicando si A es subconjunto de B.
 */
int cd_subconjunto(TablaHash A, TablaHash B);

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la unión de ambos
 */
TablaHash cd_union(TablaHash A, TablaHash B);

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la diferencia entre ambos.
 */
TablaHash cd_diferencia(TablaHash A, TablaHash B);

#endif
