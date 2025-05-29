// Implemente la mejora discutida en clase a Insertion sort. Es decir, evite los swap()s intermedios innecesarios. Mida la diferencia de rendimiento: ¿cuándo es más pronunciada?

#include <stdio.h>
#include <stdlib.h>

void insertion(int a[], int len) {
  for (int i = 1; i <= len - 1; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (a[j] > a[j + 1]) {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      } else {
        break;
      }
    }
  }
}

void insertion_opt(int a[], int len) {
    int j, elem_act;
    for(int i = 1; i < len; i++) {
        elem_act = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > elem_act) {
            a[j + 1] = a[j];
            j = j - 1;
        }

        a[j + 1] = elem_act;
    }
}

int main() {
  int a[8] = { 5, -1, 9, 10, -98, -2, 0, 53 };
  insertion_opt(a, 8);

  for (int i = 0; i < 8; i++) {
    printf("%d  ", a[i]);
  }
  printf("\n");

  return 0;
}
