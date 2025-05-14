#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);
typedef void (*FuncionVisitanteExtra)(int dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void inorder(BTree arbol, FuncionVisitante visit);
void preorder(BTree arbol, FuncionVisitante visit);
void postorder(BTree arbol, FuncionVisitante visit);
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/**
 * Recorrido del arbol preorder iterativo, utilizando la funcion pasada.
 */
void *no_copia(void *dato);
void no_destruir(void *dato);
void btree_recorrer_pre_it(BTree arbol, FuncionVisitante visit);

// Retorna el número de nodos del árbol.
int btree_nnodos(BTree arbol);

// Retorna 1 si el número dado se encuentra en el árbol, y 0 en caso contrario.
int btree_buscar(BTree arbol, int numero);

// Retorna un nuevo árbol que sea una copia del árbol dado.
BTree btree_copiar(BTree arbol);

// Retorna la altura del árbol.
int btree_altura(BTree arbol);

// Retorna el número de nodos que se encuentran a la profundidad dada.
int btree_nnodos_profundidad(BTree arbol, int profundidad);

// Retrona la profundidad del nodo que contiene el número dado, y -1 si el número no se encuentra en el árbol.
int btree_profundidad(BTree arbol, int numero);

// Retorna la suma totoal de los datos del árbol.
int btree_suma(BTree arbol);

// Recorrido del arbol, utilizando la funcion pasada y un dato extra.
void inorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra, void *extra);
void preorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra,
                    void *extra);
void postorder_extra(BTree arbol, FuncionVisitanteExtra visit_extra,
                     void *extra);
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra);

// Retorna el número de nodos del árbol con un dato extra.
void contar_nodo(int dato, void *extra);
int btree_nnodos_extra(BTree arbol);

// Retorna la suma totoal de los datos del árbol con un dato extra.
void sumar_dato(int dato, void *extra);
int btree_suma_extra(BTree arbol);

// Realiza una búsqueda por extensión
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);

#endif                          /* __BTREE_H__ */
