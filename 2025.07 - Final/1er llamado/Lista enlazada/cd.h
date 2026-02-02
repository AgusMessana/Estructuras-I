#ifndef __CD_H__
#define __CD_H__
/**
 * Funciones para manipular datos generales
 */
typedef void *(*FuncionCopiadora)(void *dato);
typedef void (*FuncionDestructora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);


/**
 * Definición de la estructura
 */
typedef struct _CDNodo {
  void *dato;
  double gp;
  struct _CDNodo *sig;
} CDNodo;
typedef CDNodo *CD;

/**
 * Crea un conjunto difuso
 */
CD cd_crear();

/**
 * Toma un CD, un elemento de tipo void* y un grado de pertenencia de tipo double y modifiqua el grado de pertenencia del elemento. 
 * Si el nuevo grado de pertenencia es 0 el elemento debe ser eliminado.
 */
CD cd_modificar_gp(CD conj, void *dato, double gp, FuncionComparadora comp,
                   FuncionDestructora dest);

/**
 * Tome un CD, un elemento de tipo void* y un grado de pertenencia de tipo double y agregua el elemento al conjunto con el grado de pertenencia dado.
 */
CD cd_agregar(CD conj, void *dato, double gp, FuncionCopiadora copy,
              FuncionComparadora comp, FuncionDestructora dest);

/**
 * Toma dos conjuntos difusos A y B y devuelva un int indicando si A es subconjunto de B.
 */
int cd_subconjunto(CD A, CD B, FuncionComparadora comp);

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la unión de ambos
 */
CD cd_union(CD A, CD B, FuncionComparadora comp, FuncionCopiadora copy,
            FuncionDestructora dest);

/**
 * Toma dos conjuntos difusos y devuelva un nuevo conjunto con la diferencia entre ambos.
 */
CD cd_diferencia(CD A, CD B, FuncionComparadora comp, FuncionCopiadora copy,
                 FuncionDestructora dest);

#endif
