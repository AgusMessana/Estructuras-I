#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);

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
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/**
 * Retorna el número de nodos del árbol.
 */
int btree_nnodos(BTree arbol);

/**
 * Retorna 1 si el número dado se encuentra en el árbol, y 0 en caso contrario.
 */
int btree_buscar(BTree arbol, int dato);

/**
 * Retorna un nuevo árbol que sea una copia del árbol dado.
 */
BTree btree_copiar(BTree arbol);

/**
 * Retorna la áltura del árbol.
 */
int btree_altura(BTree arbol);

/**
 * Retorna el número de nodos que se encuentran a la profundidad dada.
 */
int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * Retorna la profundidad del nodo que contiene el número dado, y -1 si el
 * número no se encuentra en el árbol.
 */
int btree_profundidad(BTree arbol, int dato);

/**
 * Retorna la suma total de los datos del árbol.
 */
int btree_sumar(BTree arbol);

/**
 * Dado un árbol binario, genere el árbol binario espejo donde el hijo derecho
 * de cada nodo pasa a ser izquierdo y el izquierdo pasa a ser derecho.
 */
BTree mirror(BTree arbol);

#endif /* __BTREE_H__ */
