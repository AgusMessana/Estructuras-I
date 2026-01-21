#ifndef __HYBRIDHASH_H__
#define __HYBRIDHASH_H__

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */

typedef struct _HybridHash *HybridHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
HybridHash hybrid_hash_crear(unsigned capacidad, FuncionCopiadora copia,
                             FuncionComparadora comp, FuncionDestructora destr,
                             FuncionHash hash);

/**
 * Inserta un elemento en la tabla. Si al agregar se supera el umbral, se cambia de lista a árbol. Si no, no se hace el cambio.
 * Si el elemento está repetdio, no se agrega.
 */
void hybrid_hash_insertar(HybridHash tabla, void* dato);

/**
 * Busca en la tabla un dato que coincida con el dato dado, y retorna el dato encontrado o NULL en caso de no hallarse en la tabla.
 */
void* hybrid_hash_buscar(HybridHash tabla, void* dato);

/**
 * Elimina un elemento en la tabla. Si al eliminar se baja del umbral, se cambia de árbol a lista. Si no, no se hace el cambio.
 */
void hybrid_hash_eliminar(HybridHash tabla, void* dato);
#endif
