#ifndef __CONJUNTO__H__
#define __CONJUNTO__H__

typedef int (*Operacion)(int dato1, int dato2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Dado un conjunto, devuelve 1 si el elemento está en él y 0 si no.
 */
int pertenece(SList conjunto, int dato);

/**
 * Dado un conjunto, inserta un elemento en el él. Si ya estaba, no lo inserta.
 */
SList insertar(SList conjunto, int dato);

/**
 * Dado un conjunto, un elemento de dicho conjunto que es candidato a elemento neutro y una operación de enteros, devuelve 1 si el conjunto dotado de la operación es un grupo y 0 si no
 */
int es_grupo(SList conjunto, int neutro, Operacion op);

#endif
