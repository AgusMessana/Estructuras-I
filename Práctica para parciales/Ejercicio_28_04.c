#include <stdlib.h>
#include <stdio.h>
#include "Ejercicio_28_04.h"

Cola encolar(Cola cola, void *dato, FuncionCopia copy) {
  cola.pila_encolar = gpila_apilar(cola.pila_encolar, dato, copy);
  return cola;
}

Cola desplazar(Cola cola, FuncionCopia copy, FuncionDestructora destroy) {
  if (!gpila_es_vacia(cola.pila_encolar)) {
    void *dato = gpila_tope(cola.pila_encolar);
    cola.pila_desencolar = gpila_apilar(cola.pila_desencolar, dato, copy);
    cola.pila_encolar = gpila_desapilar(cola.pila_encolar, destroy);
  }

  return cola;
}

Cola desencolar(Cola cola, FuncionCopia copy, FuncionDestructora destroy) {
  if (gpila_es_vacia(cola.pila_desencolar)) {
    cola = desplazar(cola, copy, destroy);
  }

  cola.pila_desencolar = gpila_desapilar(cola.pila_desencolar, destroy);

  return cola;
}
