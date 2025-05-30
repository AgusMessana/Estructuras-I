// Modifique la partición de Lomuto para llevar tres segmentos: menores estrictos al pivote, iguales al pivote, y mayores estrictos al pivote. Usándola, adapte Quicksort para funcionar eficientemente en arrays con muchos elementos repetidos.

#include <stdio.h>
#include <stdlib.h>

// Devuelve los índices de inicio y fin del bloque igual al pivote (por punteros)
void lomuto3(int *a, int low, int high, int *mid_start, int *mid_end) {
  int pivot = a[high];
  int i = low;                  // inicio de los menores
  int j = low;                  // cursor actual
  int k = high;                 // fin de los mayores

  while (j <= k) {
    if (a[j] < pivot) {
      // swap a[i] <-> a[j]
      int tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++;
      j++;
    } else if (a[j] > pivot) {
      // swap a[j] <-> a[k]
      int tmp = a[j];
      a[j] = a[k];
      a[k] = tmp;
      k--;
      // no incrementamos j, porque a[j] es nuevo (puede ser <, = o >)
    } else {
      j++;
    }
  }

  *mid_start = i;
  *mid_end = k;
}


void quicksort3(int *a, int low, int high) {
  if (low < high) {
    int m1, m2;
    lomuto3(a, low, high, &m1, &m2);
    quicksort3(a, low, m1 - 1);
    quicksort3(a, m2 + 1, high);
  }
}

int main() {
  int a[] = { 5, 7, 1, 2, 98, -2, 3, -10, 4 };
  int len = sizeof(a) / sizeof(int);
  quicksort3(a, 0, len - 1);

  for (int i = 0; i < len; i++) {
    printf("%d  ", a[i]);
  }
  printf("\n");

  return 0;
}
