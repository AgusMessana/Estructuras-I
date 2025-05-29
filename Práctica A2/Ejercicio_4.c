// Implemente Mergesort para arreglos, haciendo un manejo adecuado de la memoria.

#include <stdio.h>
#include <stdlib.h>

void mezclar(int *b1, int *b2, int *resultado, int len1, int len2) {
  int i = 0, j = 0, k = 0;

  // Recorremos ambos subarreglos y agregamos el menor elemento de ambos a 'resultado'
  while (i < len1 && j < len2) {
    if (b1[i] < b2[j]) {
      resultado[k++] = b1[i++];
    } else {
      resultado[k++] = b2[j++];
    }
  }

  // Si quedaron elementos en B1, los agregamos al final
  while (i < len1) {
    resultado[k++] = b1[i++];
  }

  // Si quedaron elementos en B2, los agregamos al final
  while (j < len2) {
    resultado[k++] = b2[j++];
  }
}

int *mergesort(int *a, int len) {

  // Caso base: si el arreglo tiene menos de 2 elementos, ya está ordenado
  if (len < 2) {
    int *copia = malloc(sizeof(int) * len);
    if (len > 0) {
      copia[0] = a[0];          // Solo copiamos si hay un elemento
    }
    return copia;               // Devolvemos la copia como nuevo arreglo
  } else {
    int m = len / 2;

    // Caso recursivo: dividimos el arreglo en dos mitades
    int *a1 = a;                // Primera mitad: A[0 .. m-1]
    int *a2 = a + m;            // Segunda mitad: A[m .. N-1]

    // Aplicamos mergesort recursivamente a cada mitad
    int *b1 = mergesort(a1, m); // Ordenamos la primera mitad
    int *b2 = mergesort(a2, len - m);   // Ordenamos la segunda mitad

    int *resultado = malloc(sizeof(int) * len);
    mezclar(b1, b2, resultado, m, len - m);

    free(b1);
    free(b2);

    return resultado;
  }
}

int main() {
  int a[8] = { 5, -1, 9, 10, -98, -2, 0, 53 };
  int *ordenado = mergesort(a, 8);

  for (int i = 0; i < 8; i++) {
    printf("%d  ", ordenado[i]);
  }
  printf("\n");

  return 0;
}
