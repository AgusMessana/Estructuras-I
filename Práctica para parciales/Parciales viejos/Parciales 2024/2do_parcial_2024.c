#include <stdio.h>
#include <stdlib.h>
#include "2do_parcial_2024.h"

/**
 * Crea un árbol 2 − 3 vacío.
 */
Arbol23 arbol_crear() {
  return NULL;
}

/**
 * Recibe un árbol 2 − 3 y devuelve la cantidad de valores que guarda el nodo
 * raíz.
 */
int cantidad_de_valores(Arbol23 t) {
  if (t == NULL) {
    return 0;
  }
  if (t->right == CENTINELA) {
    return 1;
  }
  return 2;
}

/**
 * Dado un valor y dos árboles 2−3 crea un nodo binario con el valor como dato
 * y los dos árboles como hijos.
 */
Arbol23 crear_nodo_binario(int x, Arbol23 l, Arbol23 r) {
  Arbol23 nuevoArbol = malloc(sizeof(struct nodo_arbol23));
  nuevoArbol->k1 = x;
  nuevoArbol->k2 = 0;
  nuevoArbol->left = l;
  nuevoArbol->middle = r;
  nuevoArbol->right = CENTINELA;

  return nuevoArbol;
}

/**
 * Inserta el valor x en el árbol t siguiendo las reglas de inserción del árbol
 * 2 − 3 y conservando sus invariantes.
 * En caso de saturarse t, la función devuelve 1 (true) y guarda en out_l el subárbol izquierdo, en out_r el subárbol derecho y en out_x el dato.
 * En caso de no saturarse t, la función devuelve 0 (false) y no guarda nada en los punteros pasados por argumento.
 */
int insertar_impl(Arbol23 t, int x, int *out_x, Arbol23 * out_l,
                  Arbol23 * out_r) {
  //Caso base: árbol vacío
  if (t == NULL) {
    *out_x = x;
    *out_l = NULL;
    *out_r = NULL;

    return 1;
  }
  // Es hoja
  if (t->left == NULL) {
    if (t->right == CENTINELA) {
      //Nodo binario. Expandir a ternario
      if (x < t->k1) {
        t->k2 = t->k1;
        t->k1 = x;
      } else {
        t->k2 = x;
      }
      t->right = NULL;
      return 0;
    } else {
      //Nodo ternario. Saturación y dividir
      int v1 = t->k1, v2 = t->k2;
      if (x < v1) {
        *out_x = v1;
        *out_l = crear_nodo_binario(x, NULL, NULL);
        *out_r = crear_nodo_binario(v2, NULL, NULL);
      } else if (x < v2) {
        *out_x = x;
        *out_l = crear_nodo_binario(v1, NULL, NULL);
        *out_r = crear_nodo_binario(v2, NULL, NULL);
      } else {
        *out_x = x;
        *out_l = crear_nodo_binario(v1, NULL, NULL);
        *out_r = crear_nodo_binario(v2, NULL, NULL);
      }

      return 1;
    }
  }
  // Nodo interno → insertar recursivamente en la rama correcta
  Arbol23 l = t->left, m = t->middle, r = t->right;
  int mid_val;
  Arbol23 child_l, child_r;

  if (x < t->k1) {
    if (insertar_impl(l, x, &mid_val, &child_l, &child_r)) {
      if (r == CENTINELA) {
        // Era binario, se puede expandir
        t->k2 = t->k1;
        t->k1 = mid_val;
        t->right = t->middle;
        t->left = child_l;
        t->middle = child_r;
        return 0;
      } else {
        // Nodo ternario → split
        *out_x = t->k1;
        *out_l = crear_nodo_binario(mid_val, child_l, child_r);
        *out_r = crear_nodo_binario(t->k2, m, r);
        return 1;
      }
    }
  } else if (r == CENTINELA || x < t->k2) {
    if (insertar_impl(m, x, &mid_val, &child_l, &child_r)) {
      if (r == CENTINELA) {
        // Era binario, se puede expandir
        t->k2 = mid_val;
        t->right = child_r;
        t->middle = child_l;
        return 0;
      } else {
        // Nodo ternario → split
        *out_x = mid_val;
        *out_l = crear_nodo_binario(t->k1, l, child_l);
        *out_r = crear_nodo_binario(t->k2, child_r, r);
        return 1;
      }
    }
  } else {
    if (insertar_impl(r, x, &mid_val, &child_l, &child_r)) {
      // Solo entra si t ya es ternario → split obligatorio
      *out_x = t->k2;
      *out_l = crear_nodo_binario(t->k1, l, m);
      *out_r = crear_nodo_binario(mid_val, child_l, child_r);
      return 1;
    }
  }

  return 0;                     // No hubo saturación
}

////////////////////////////////////////////////////////////////////////////////

// Intercambia los valores entre dos punetros a entero .
void swap_int(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// Devuelve la posicion del padre del elemento en la posicion i
int padre(int i) {
  return (i - 1) / 2;
}

// Devuelve la posicion del hijo izquierdo del elemento en la posicion i
int izq(int i) {
  return i * 2 + 1;
}

// Devuelve la posicion del hijo derecho del elemento en la posicion i
int der(int i) {
  return i * 2 + 2;
}

// Hunde el elemento en la posicion pos del arreglo hasta que este cumpla la condicion de max - heap. n es la cantidad de elementos del arreglo
void hundir(int pos, int *arr, int n) {
  int max_pos = pos;
  if (izq(pos) < n && arr[izq(pos)] > arr[max_pos])
    max_pos = izq(pos);
  if (der(pos) < n && arr[der(pos)] > arr[max_pos])
    max_pos = der(pos);
  if (max_pos != pos) {
    swap_int(&arr[pos], &arr[max_pos]);
    hundir(max_pos, arr, n);
  }
}

// Flota el elemento en la posicion pos hasta que el arreglo cumpla con la condicion de max - heap . n es la cantidad de elementos del arreglo .
void flotar(int pos, int *arr, int n) {
  if (pos == 0)
    return;
  int pos_padre = padre(pos);
  if (arr[pos_padre] < arr[pos]) {
    swap_int(&arr[pos], &arr[pos_padre]);
    flotar(pos_padre, arr, n);
  }
}

/**
 * Implementa un algoritmo de ordenamiento in-place, es decir, que ordene el
 * arreglo arr de tamaño n dentro del espacio de memoria dado en lugar de
 * devolver un nuevo arreglo ordenado, utilizando las funciones de manipulación
 * de max-heap definidas previamente. 
 * Esta función debe definirse de la manera más eficiente posible ya que se
 * evaluará la eficiencia del algoritmo. Además, no deben utilizarse
 * estructuras adicionales. 
 */
void ordenar(int *arr, int n) {
  // Paso 1: construir el max-heap (de atrás hacia adelante)
  for (int i = padre(n - 1); i >= 0; i--) {
    hundir(i, arr, n);
  }

  // Paso 2: ordenar extrayendo el máximo y hundiendo
  for (int i = n - 1; i >= 0; i--) {
    swap_int(&arr[0], &arr[i]); // Poner el máximo al final
    hundir(0, arr, i);          // Restaurar heap (tamaño i)
  }
}
