// Implemente búsqueda binaria sobre un arreglo ordenado de enteros. Devolver el índice i en donde se encuentra el valor v, o −1 si no aparece en el array.

#include <stdio.h>
#include <stdlib.h>

int binsearch(int a[], int len, int v) {
  int low = 0;
  int high = len - 1;
  while (low <= high) {
    int medio = (low + high) / 2;

    if (v == a[medio]) {
      return medio;
    } else if (v < a[medio]) {
      high = medio - 1;
    } else if (v > a[medio]) {
      low = medio + 1;
    }
  }

  return -1;
}

int main() {
  int a[6] = { 1, 4, 5, 16, 20 };
  int v;
  printf("Ingrese un número entero: \n");
  scanf("%d", &v);

  int encontrado = binsearch(a, 6, v);
  if (encontrado == -1) {
    printf("El valor %d no está en el arreglo.\n", v);
  } else {
    printf("El valor %d se encuentra en la posición %d del arreglo.\n", v,
           encontrado);
  }

  return 0;
}
