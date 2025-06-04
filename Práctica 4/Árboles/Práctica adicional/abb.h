#ifndef __ABB_H__
#define __ABB_H__

typedef void (*FuncionVisitante)(int *dato);

struct _BST_Nodo {
  int dato;
  struct _BST_Nodo *izq, *der;
};

typedef struct _BST_Nodo *BSTree;

/**
 * Dado un entero k, busque en el árbol binario de búsqueda el menor
 * entero mayor a k.
 */
int bstree_cota_inferior(BSTree arbol, int k);

/**
 * Visita los datos en el intervalo [cota inf, cota sup].
 */
void bstree_recorrer_intervalo(BSTree arbol, int cota_inf, int cota_sup,
                               FuncionVisitante visit);

/**
 * Dado un arreglo con los datos del recorrido PRE ORDER de un árbol
 * binario de busqueda, reconstruya el arbol.
 */

/**
 * Dada una secuencia de datos, determina si corresponde al recorrido BFS
 * de un árbol binario de búsqueda completo y, en dicho caso, lo
 * construya de manera eficiente.
 */

#endif
