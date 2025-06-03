#include <stdio.h>
#include <stdlib.h>
#include "bheaps.h"

// Función copiadora para enteros
void *copiar_int(void *dato) {
  if (dato == NULL)
    return NULL;
  int *nuevo = malloc(sizeof(int));
  if (nuevo == NULL)
    return NULL;
  *nuevo = *(int *) dato;
  return nuevo;
}

// Función comparadora para enteros (max-heap)
int comparar_int(void *a, void *b) {
  return *(int *) a - *(int *) b;
}

// Función visitante para enteros
void imprimir_int(void *dato) {
  printf("%d ", *(int *) dato);
}

/**
 * Función destructora para datos de tipo int.
 * Libera la memoria asignada a un entero.
 */
void dest_int(void *dato) {
  if (dato != NULL) {
    free(dato);                 // Liberamos el entero previamente asignado con malloc
  }
}

int main() {
  // Arreglo de prueba
  int valores[] = { 7, 3, 10, 1, 6, 8, 14, 2, 5, 9 };
  int largo = sizeof(valores) / sizeof(int);

  // Crear arreglo de punteros
  void **arr = malloc(sizeof(void *) * largo);
  for (int i = 0; i < largo; i++) {
    arr[i] = &valores[i];
  }

  // Crear heap desde arreglo
  BHeap heap = bheap_crear_desde_arr(arr, largo, copiar_int, comparar_int);
  free(arr);                    // Liberar el arreglo temporal

  // Verificar si la creación fue exitosa
  if (heap == NULL) {
    printf("Error al crear el heap\n");
    return 1;
  }
  // Recorrer e imprimir
  printf("Heap construido:\n");
  bheap_recorrer(heap, imprimir_int);

  // Verificar raíz
  if (heap->ultimo > 0) {       // Asegurarse que hay elementos
    printf("\nRaíz (máximo): %d\n", *(int *) heap->arr[1]);
  }
  // Liberar memoria correctamente
  bheap_destruir(heap, dest_int);
  return 0;
}
