// Diseñe un algoritmo que dado un arreglo A de tamaño n calcule la mediana del mismo. Puede modificar al arreglo que recibe como argumento. (Pista: la mediana es el elemento medio del arreglo ordenado.) Su función debería ser mejor que O(nlgn) en el caso promedio.

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

int quickselect(int *a, int low, int high, int k) {
  if (low == high)
    return a[low];

  int pivot_index = lomuto(a, low, high);       // misma partición que QuickSort

  int left_count = pivot_index - low;   // elementos antes del pivote

  if (k == pivot_index)
    return a[k];
  else if (k < pivot_index)
    return quickselect(a, low, pivot_index - 1, k);
  else
    return quickselect(a, pivot_index + 1, high, k);
}

int find_median(int *a, int n) {
  if (n % 2 == 1)
    return quickselect(a, 0, n - 1, n / 2);     // impar
  else {
    int m1 = quickselect(a, 0, n - 1, n / 2 - 1);
    int m2 = quickselect(a, 0, n - 1, n / 2);
    return (m1 + m2) / 2;
  }
}

int main() {
  int a[] = { 7, 1, 5, 3, 9, 2, 8 };    // Mediana: 5
  int n = sizeof(a) / sizeof(int);

  int mediana = find_median(a, n);
  printf("La mediana es: %d\n", mediana);

  return 0;
}
