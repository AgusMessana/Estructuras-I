#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

typedef struct _BST_Nodo *BSTree;
typedef struct _BTNodo *BTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstee_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree, BSTreeRecorrido, FuncionVisitanteExtra,
                     void *extra);

/**
 * Elimina, si es posible, un elemento del arbol. El arbol resultante debe ser * nuevamente un ABB.
 */
BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora,
                       FuncionDestructora, FuncionCopiadora);

/**
 * Dado un indice k devuelve el k-ésimo menor elemento del árbol,
 * de no encontrarlo devuelve NULL.
 */
void *bstree_k_esimo_menor(BSTree, int);

/**
 * Determina si el árbol dado cumple la propiedad de los ABB. Devuelve 1 si lo hace, 0 si no.
 */
int btree_validar(BTree);
#endif                          //__BSTREE_H__
