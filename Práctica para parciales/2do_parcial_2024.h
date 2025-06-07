#ifndef __2DO_PARCIAL_2024_H__
#define __2DO_PARCIAL_2024_H__
#include <stddef.h>

typedef struct nodo_arbol23 *Arbol23;
// Representa un arbol especial utilizado para marcar que un arbol es binario poniendolo como tercer hijo
#define CENTINELA (( Arbol23 )1)
// Nodo de arbol 2-3
// Los nodos con un solo valor ( solo dos hijos ) tienen right = CENTINELA
struct nodo_arbol23 {
  int k1, k2;
  Arbol23 left, middle, right;
};
/**
 * k1 < k2;
 * los datos de left se asumen menores a k1;
 * los datos de middle se asumen mayores a k1 y menores a k2;
 * los datos de right se asumen mayores a k2;
 */

/**
 * Crea un árbol 2 − 3 vacío.
 */
Arbol23 arbol_crear();

/**
 * Recibe un árbol 2 − 3 y devuelve la cantidad de valores que guarda el nodo
 * raíz.
 */
int cantidad_de_valores(Arbol23 t);

/**
 * Dado un valor y dos árboles 2−3 crea un nodo binario con el valor como dato
 * y los dos árboles como hijos.
 */
Arbol23 crear_nodo_binario(int x, Arbol23 l, Arbol23 r);

/**
 * Inserta el valor x en el árbol t siguiendo las reglas de inserción del árbol
 * 2 − 3 y conservando sus invariantes.
 * En caso de saturarse t, la función devuelve 1 (true) y guarda en out_l el subárbol izquierdo, en out_r el subárbol derecho y en out_x el dato.
 * En caso de no saturarse t, la función devuelve 0 (false) y no guarda nada en los punteros pasados por argumento.
 */
int insertar_impl(Arbol23 t, int x, int *out_x, Arbol23 * out_l,
                  Arbol23 * out_r);

////////////////////////////////////////////////////////////////////////////////

// Intercambia los valores entre dos punetros a entero .
void swap_int(int *x, int *y);

// Devuelve la posicion del padre del elemento en la posicion i
int padre(int i);

// Devuelve la posicion del hijo izquierdo del elemento en la posicion i
int izq(int i);

// Devuelve la posicion del hijo derecho del elemento en la posicion i
int der(int i);

// Hunde el elemento en la posicion pos del arreglo hasta que este cumpla la condicion de max - heap . n es la cantidad de elementos del arreglo
void hundir(int pos, int *arr, int n);

// Flota el elemento en la posicion pos hasta que el arreglo cumpla con la condicion de max - heap. n es la cantidad de elementos del arreglo .
void flotar(int pos, int *arr, int n);

/**
 * Implementa un algoritmo de ordenamiento in-place, es decir, que ordene el
 * arreglo arr de tamaño n dentro del espacio de memoria dado en lugar de
 * devolver un nuevo arreglo ordenado, utilizando las funciones de manipulación
 * de max-heap definidas previamente. 
 * Esta función debe definirse de la manera más eficiente posible ya que se
 * evaluará la eficiencia del algoritmo. Además, no deben utilizarse
 * estructuras adicionales. 
 */
void ordenar(int *arr, int n);
#endif
