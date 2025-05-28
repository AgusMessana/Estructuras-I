#include "bstree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
};

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() {
  return NULL;
}

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0)  // dato < raiz->dato. Significa que el dato es más chico que el de la raíz, por lo que hay que buscar a la izquierda.
    return bstree_buscar(raiz->izq, dato, comp);
  else                          // raiz->dato < dato. Significa que el dato es más grande que el de la raíz, por lo que hay que buscar a la izquierda.
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia,
                       FuncionComparadora comp) {
  if (raiz == NULL) {           // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));     // también puedo hacer BSTree *nuevoNodo...
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0)        // dato < raiz->dato. Significa que el dato es más chico que el de la raíz, por lo que hay que buscar a la izquierda.
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0)  // raiz->dato < dato. Significa que el dato es más grande que el de la raíz, por lo que hay que buscar a la izquierda.
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,
                     FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)   // visito el nodo antes de recorrer los hijos → visita() se llama antes de los dos llamados recursivos.
      visita(raiz->dato, extra);

    bstree_recorrer(raiz->izq, orden, visita, extra);

    if (orden == BTREE_RECORRIDO_IN)    // visito el nodo entre los hijos → visita() se llama entre los dos llamados recursivos.
      visita(raiz->dato, extra);

    bstree_recorrer(raiz->der, orden, visita, extra);

    if (orden == BTREE_RECORRIDO_POST)  // visito el nodo después de recorrer los hijos → visita() se llama después de los dos llamados recursivos.
      visita(raiz->dato, extra);
  }
}

/**
 * Elimina, si es posible, un elemento del arbol. El arbol resultante debe ser * nuevamente un ABB.
 */
BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora comp,
                       FuncionDestructora destr, FuncionCopiadora copia) {
  if (arbol == NULL) {
    return NULL;
  }

  if (comp(dato, arbol->dato) < 0) {
    arbol->izq = bstree_eliminar(arbol->izq, dato, comp, destr, copia);
  } else if (comp(dato, arbol->dato) > 0) {
    arbol->der = bstree_eliminar(arbol->der, dato, comp, destr, copia);
  } else {
    if (arbol->izq == NULL) {
      BSTree temp = arbol->der;
      destr(arbol->dato);
      free(arbol);
      return temp;
    } else if (arbol->der == NULL) {
      BSTree temp = arbol->izq;
      destr(arbol->dato);
      free(arbol);
      return temp;
    } else {                    //debo encontrar el valor más pequeño entre los más grandes del nodo a eliminar. Luego, ese valor lo pongo en el nodo a eliminar. Así, los nodos a la derecha seguirán siendo más grandes que ese nuevo nodo, y se mantiene el ABB.
      BSTree sucesor = arbol->der;
      while (sucesor->izq != NULL) {
        sucesor = sucesor->izq;
      }
      arbol->dato = copia(sucesor->dato);
      arbol->der =
          bstree_eliminar(arbol->der, sucesor->dato, comp, destr, copia);
      return arbol;
    }
  }

  return arbol;
}

/**
  * Función auxiliar utilizada por bstree_k_esimo_menor para
  * guardar el valor de k en cada llamada recursiva. 
  */
static void *bstree_k_esimo_menor_aux(BSTree arbol, int *k) {
  /* Si el árbol es vacío no hay elementos. */
  if (bstree_es_vacio(arbol))
    return NULL;
  void *dato;
  /* Llamada recursiva al subárbol izquierdo. */
  dato = bstree_k_esimo_menor_aux(arbol->izq, k);
  if (dato != NULL)
    /* Si el dato no es NULL ya encontré el dato en el subárbol izquierdo. */
    return dato;
  /* Veo el nodo actual */
  if (*k == 0)
    /* Se está retornando la dirección del dato dentro del árbol.
       Si en el main de modifica o libera el dato devuelto por esta función,
       también se modificará dentro de esta estuctura. */
    return arbol->dato;
  --(*k);
  /* Llamada recursiva al subárbol derecho */
  return bstree_k_esimo_menor_aux(arbol->der, k);
}

/**
 * Dado un indice k devuelve el k-ésimo menor elemento del árbol,
 * de no encontrarlo devuelve NULL.
 */
void *bstree_k_esimo_menor(BSTree arbol, int k) {
  /* La idea es recorrer el árbol usando el algoritmo de busqueda en profundidad
     visitando los datos de forma inorder (es decir, de menor a mayor). 
     Cada vez que se visita un dato, se reduce el contador en 1 y cuando este se haga 0, 
     el recorrido habra llegado al nodo buscado. Se usa un puntero a un entero porque todas
     las llamadas recursivas deben tener acceso a la misma variable contador 
     (recordar que en c los parámetros se pasan por valor) */
  return bstree_k_esimo_menor_aux(arbol, &k);
}

/**
 * Determina si el árbol dado cumple la propiedad de los ABB. Devuelve 1 si lo hace, 0 si no.
 */
int btree_validar(BTree) {
  
}
