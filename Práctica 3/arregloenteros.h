#ifndef __ARREGLOENTEROS_H__
#define __ARREGLOENTEROS_H__

#include <stddef.h>

typedef struct {
  int *datos;
  int capacidad;
} ArregloEnteros;

// Crea un arreglo de enteros
ArregloEnteros *arreglo_enteros_crear(int capacidad);

// Destruye un arreglo de enteros existente
void arreglo_enteros_destruir(ArregloEnteros * arreglo);

// Devuelve el entero en la posición dada
int arreglo_enteros_leer(ArregloEnteros * arreglo, int pos);

// Agrega un entero en la posición dada
void arreglo_enteros_escribir(ArregloEnteros * arreglo, int pos, int dato);

// Devuelve la longitud del arreglo
int arreglo_enteros_capacidad(ArregloEnteros * arreglo);

// Imprime los enteros del arreglo
void arreglo_enteros_imprimir(ArregloEnteros * arreglo);

// Ajusta el tamaño del arreglo. 
// Si la nueva capacidad es menor, el contenido debe ser truncado.
void arreglo_enteros_ajustar(ArregloEnteros * arreglo, int capacidad);

// Inserta el dato en la posicion dada, moviendo todos los elementos desde esa posicion un lugar a la derecha
void arreglo_enteros_insertar(ArregloEnteros * arreglo, int pos, int dato);

// Elimina el dato en la posicion dada, moviendo todos los elementos posteriores un lugar a la izquierda
void arreglo_enteros_eliminar(ArregloEnteros * arreglo, int pos);

#endif