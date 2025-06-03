#ifndef __COLA_PRIORIDAD_H__
#define __COLA_PRIORIDAD_H__
#include "bheaps.h"
typedef struct {
  BHeap heap;
} *ColaPrioridad;

/**
 * Retorna 1 si la cola esta vacía y 0 en caso contrario.
 */
int cola_de_prioridad_es_vacia(ColaPrioridad cola);

/**
 * Retorna el elemento prioritario de la cola.
 */
void *cola_prioridad_maximo(ColaPrioridad cola);

/**
 * Elimina el elemento prioritario de la cola.
 */
void cola_prioridad_eliminar_maximo(ColaPrioridad cola,
                                    FuncionDestructora dest);

/**
 * Inserta un elemento en la cola con una determinada prioridad.
 */
void *cola_prioridad_insertar(ColaPrioridad cola, void *dato,
                              FuncionCopiadora copy);
#endif
