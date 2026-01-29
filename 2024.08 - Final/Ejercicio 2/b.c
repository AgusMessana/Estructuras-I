#include <stdio.h>
#include <stdlib.h>

#define TAM 9
#define VACIO -1

int h(int x) {
  return x % TAM;
}

int buscar(int tabla[], int x) {
  int pos = h(x);
  int inicio = pos;

  while (tabla[pos] != VACIO) {
    if (tabla[pos] == x) {
      return 1;
    }
    pos = (pos + 1) % TAM;

    if (pos == inicio) {
      break;
    }
  }

  return 0;
}
