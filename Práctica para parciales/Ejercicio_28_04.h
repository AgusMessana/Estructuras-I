#ifndef __EJERCICIO_28_04_H__
#define __EJERCICIO_28_04_H__
#include <stddef.h>
#include "Estructuras-I/Práctica 3/gpilas.h"

typedef struct _Cola {
  Pila pila_encolar;
  Pila pila_desencolar;
} Cola;

Cola encolar(Cola cola, void *dato, FuncionCopia copy);

Cola desplazar(Cola cola, FuncionCopia copy, FuncionDestructora destroy);

Cola desencolar(Cola cola, FuncionCopia copy, FuncionDestructora destroy);

#endif
