#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */

typedef struct _TablaHash *TablaHash;

/**
 * Crea una Tabla Hash con la capacidad y funciones dadas.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora dest,
                          FuncionHash hash);

/**
 * Destrutye una Tabla Hash.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Devuelve el elemento buscado si está en la tabla o NULL si no está.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Inserta un elemento en la Tabla Hash.
 */
void tablahash_insertar(TablaHash tabla, void *dato);


/**
 * Elimina un elemento dado de la tabla si está, y no hace nada si no está
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

/**
 * Devuelve la cantidad de elementos de la tabla.
 */
unsigned tablahash_numElems(TablaHash tabla);

/**
 * Devuelve la capacidad de la tabla.
 */
unsigned tablahash_capacidad(TablaHash tabla);

/**
 * Inserta un elemento en la Tabla Hash y hace rehash de ser necesario.
 */
void tablahash_insertar_balance(TablaHash tabla, void *dato);

#endif
