#include <stdio.h>
#include <stdlib.h>

#define TAM 9
#define VACIO -1 
// Suponemos que las casillas vacías se marcan con un -1, y que no habrá valores negativos en la tabla.
// En el siguiente inciso se propone una idea mejor, sin tener que utilizar valores como marcas.

int h(int x) {
  return x % TAM;
}

int buscar(int tabla[], int x) {
  int pos = h(x);
  int inicio = pos;
  int salir = 0;

  while (tabla[pos] != VACIO && salir != 1) {
    if (tabla[pos] == x) {
      return pos;
    }
    pos = (pos + 1) % TAM;

    if (pos == inicio) {
      salir = 1;
    }
  }

  // Retornamos -1 porque sería una posición inválida
  return -1;
}

int main(void) {
  int tabla[TAM] = {9, 18, -1, 12, 3, 14, 4, 21, -1};
  int val1 = 9;
  int val2 = 21;
  int val3 = 11;

  int esta1 = buscar(tabla, val1);
  int esta2 = buscar(tabla, val2);
  int esta3 = buscar(tabla, val3);

  if(esta1 != -1) {
    printf("El valor %d esta en la posición %d\n", val1, esta1);
  } else {
    printf("El valor %d no esta en la tabla.\n", val1);
  }

  if(esta2 != -1) {
    printf("El valor %d esta en la posición %d\n", val2, esta2);
  } else {
    printf("El valor %d no esta en la tabla.\n", val2);
  }

  if(esta3 != -1) {
    printf("El valor %d esta en la posición %d\n", val3, esta3);
  } else {
    printf("El valor %d no esta en la tabla.\n", val3);
  }

  return 0;
}