// Implemente Quicksort con la partición de Lomuto como se vio en clase. Compare el rendimiento contra Mergesort, tanto en arreglos aleatorios como en sus peores casos.

#include <stdio.h>
#include <stdlib.h>

int lomuto(int *a, int low, int high) {
  int pivote = a[high];
  int i = low - 1;
  int temp = 0;

  for (int j = low; j < high; j++) {
    if (a[j] <= pivote) {
      i++;
      temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
  }

  temp = a[i + 1];
  a[i + 1] = a[high];
  a[high] = temp;


  return i + 1;
}

void quicksort(int *a, int low, int high) {
  if (low < high) {
    int indice_pivote = lomuto(a, low, high);
    quicksort(a, low, indice_pivote - 1);
    quicksort(a, indice_pivote + 1, high);
  }
}

int main() {
  int a[] = { 5, 7, 1, 2, 98, -2, 3, -10, 4 };
  int len = sizeof(a) / sizeof(int);
  quicksort(a, 0, len - 1);

  for (int i = 0; i < len; i++) {
    printf("%d  ", a[i]);
  }
  printf("\n");

  return 0;
}
