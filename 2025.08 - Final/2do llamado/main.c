#include <stdio.h>
#include <stdlib.h>
#include <conjunto.h>

int multiplicacion(int val1, int val2) {
  return val1 * val2;
}

int suma(int val1, int val2) {
  return val1 + val2;
}

int resta(int val1, int val2) {
  return val1 - val2;
}

int and(int val1, int val2) {
  return val1 && val2;
}

int xor(int val1, int val2) {
  return val1 != val2;
}

int main(void) {
  SList conjunto1 = NULL;
  conjunto1 = insertar(conjunto1, 0);
  conjunto1 = insertar(conjunto1, 1);
  conjunto1 = insertar(conjunto1, -1);
  conjunto1 = insertar(conjunto1, 2);
  conjunto1 = insertar(conjunto1, -3);

  SList conjunto2 = NULL;
  conjunto2 = insertar(conjunto2, 0);
  conjunto2 = insertar(conjunto2, -1);
  conjunto2 = insertar(conjunto2, 1);

  SList conjunto3 = NULL;
  conjunto3 = insertar(conjunto3, 0);
  conjunto3 = insertar(conjunto3, 1);

  SList conjunto4 = NULL;
  conjunto4 = insertar(conjunto4, 0);
  conjunto4 = insertar(conjunto4, 1);

  int grupo1, grupo2, grupo3, grupo4;
  grupo1 = es_grupo(conjunto1, 0, multiplicacion);
  grupo2 = es_grupo(conjunto2, 0, suma);
  grupo3 = es_grupo(conjunto3, 1, and);
  grupo4 = es_grupo(conjunto4, 0, xor);

  if (grupo1 == 0) {
    printf("El conjunto 1 con elemento neutro 0 no es grupo.\n");
  } else {
    printf("El conjunto 1 con elemento neutro 0 es grupo.\n");
  }

  if (grupo2 == 0) {
    printf("El conjunto 2 con elemento neutro 0 no es grupo.\n");
  } else {
    printf("El conjunto 2 con elemento neutro 0 es grupo.\n");
  }

  if (grupo3 == 0) {
    printf("El conjunto 3 con elemento neutro 1 no es grupo.\n");
  } else {
    printf("El conjunto 3 con elemento neutro 1 es grupo.\n");
  }

  if (grupo4 == 0) {
    printf("El conjunto 4 con elemento neutro 0 no es grupo.\n");
  } else {
    printf("El conjunto 4 con elemento neutro 0 es grupo.\n");
  }

  return 0;
}
