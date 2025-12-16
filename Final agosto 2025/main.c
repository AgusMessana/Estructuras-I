#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tablahash.h"
#include "utils.h"

typedef struct {
  char *nombre, *direccion, *dni;
  int edad;
} Persona;

void *FuncionCopiadora(void *dato) {
  assert(dato != NULL);
  Persona *p = (Persona *) dato;

  Persona *q = malloc(sizeof(Persona));
  assert(q != NULL);

  q->edad = p->edad;

  if (p->nombre != NULL) {
    q->nombre = malloc(strlen(p->nombre) + 1);
    assert(q->nombre != NULL);
    strcpy(q->nombre, p->nombre);
  } else {
    q->nombre = NULL;
  }

  if (p->direccion != NULL) {
    q->direccion = malloc(strlen(p->direccion) + 1);
    assert(q->direccion != NULL);
    strcpy(q->direccion, p->direccion);
  } else {
    q->direccion = NULL;
  }

  if (p->dni != NULL) {
    q->dni = malloc(strlen(p->dni) + 1);
    assert(q->dni != NULL);
    strcpy(q->dni, p->dni);
  } else {
    q->dni = NULL;
  }

  return q;
}

int FuncionComparadora(void *dato1, void *dato2) {
  assert(dato1 != NULL && dato2 != NULL);
  Persona *p = (Persona *) dato1;
  Persona *q = (Persona *) dato2;

  return strcmp(p->dni, q->dni);
}

void FuncionDestructora(void *dato) {
  assert(dato != NULL);
  Persona *p = (Persona *) dato;

  free(p->dni);
  free(p->direccion);
  free(p->nombre);
  free(p);
}

unsigned FuncionHash(void *dato) {
  assert(dato != NULL);
  Persona *p = (Persona *) dato;
  assert(p->dni != NULL);

  return KRHash(p->dni);
}

Persona *crear_persona(char *nombre, char *direccion, char *dni, int edad) {
  Persona *nuevaPersona = malloc(sizeof(Persona));
  assert(nuevaPersona != NULL);

  nuevaPersona->nombre = malloc(strlen(nombre) + 1);
  assert(nuevaPersona->nombre != NULL);
  strcpy(nuevaPersona->nombre, nombre);

  nuevaPersona->direccion = malloc(strlen(direccion) + 1);
  assert(nuevaPersona->direccion != NULL);
  strcpy(nuevaPersona->direccion, direccion);

  nuevaPersona->dni = malloc(strlen(dni) + 1);
  assert(nuevaPersona->dni != NULL);
  strcpy(nuevaPersona->dni, dni);

  nuevaPersona->edad = edad;

  return nuevaPersona;
}

int main(void) {
  TablaHash tabla = tablahash_crear(2, FuncionCopiadora, FuncionComparadora,
                                    FuncionDestructora, FuncionHash);
  Persona *p = crear_persona("Carlos", "Avellaneda 5000", "25364891", 50);
  Persona *q = crear_persona("Manolo", "Juan Perez 41", "12987654", 68);

  tablahash_insertar(tabla, p);
  tablahash_insertar(tabla, q);
  FuncionDestructora(p);
  FuncionDestructora(q);

  Persona clave;
  clave.nombre = NULL;
  clave.direccion = NULL;
  clave.edad = 0;
  clave.dni = "25364891";
  Persona *res = tablahash_buscar(tabla, &clave);
  if (res != NULL) {
    printf("Encontrado: %s\n", res->nombre);
  } else {
    printf("No encontrado\n");
  }

  tablahash_eliminar(tabla, &clave);
  res = tablahash_buscar(tabla, &clave);
  if (res == NULL) {
    printf("Eliminado \n");
  } else {
    printf("No eliminado\n");
  }

  tablahash_destruir(tabla);
  return 0;
}
