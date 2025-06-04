#ifndef __AB_H__
#define __AB_H__

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

typedef struct Cola {
    BTNodo** array;
    int frente;
    int final;
    int capacidad;
} Cola;

typedef struct _BTNodo *BTree;

/**
 * Dado un árbol binario, genere el árbol binario espejo, donde el hijo
 * derecho de cada nodo pasa a ser izquierdo y el izquierdo pasa a ser
 * derecho.
 */
BTree mirror(BTree arbol);

/**
 * Determina si el árbol es completo o no. Devuelve 1 si lo es y 0 si no.
 */
int btree_es_completo(BTree arbol);
#endif
