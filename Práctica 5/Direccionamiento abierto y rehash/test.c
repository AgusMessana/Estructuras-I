#include "contacto.h"
#include "tablahash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 11

/**
 * Caso de prueba: Tabla hash para contactos
 */
int main() {

  // Iniciar tabla hash
  TablaHash tabla = tablahash_crear(CAPACIDAD_INICIAL,
                                    (FuncionCopiadora) contacto_copia,
                                    (FuncionComparadora) contacto_comparar,
                                    (FuncionDestructora) contacto_destruir,
                                    (FuncionHash) contacto_heashear);

  // Contactos
  Contacto *agenda[6];
  agenda[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  agenda[1] = contacto_crear("Moni Argento", "3412684759", 60);
  agenda[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  agenda[3] = contacto_crear("Paola Argento", "3416259862", 29);
  agenda[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  agenda[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 6; ++i) {
    unsigned idx_base =
        contacto_heashear(agenda[i]) % tablahash_capacidad(tabla);

    printf("Insertando el contacto: ");
    contacto_imprimir(agenda[i]);
    printf(" (hash base = %u)\n", idx_base);

    int nAntes = tablahash_nelems(tabla);
    tablahash_insertar(tabla, agenda[i]);
    int nDespues = tablahash_nelems(tabla);

    int pos_real = tablahash_posicion(tabla, agenda[i]);
    printf("\tGuardado finalmente en la casilla %d.\n", pos_real);

    if (nDespues == nAntes)
      printf("\t(Sobrescritura: contacto ya existente)\n");
    else
      printf("\t(Insercion correcta – direccionamiento abierto)\n");
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");

    Contacto *ret = tablahash_buscar(tabla, agenda[i]);

    if (ret != NULL)
      printf("\tSe encuentra en la tabla (casilla %d).\n",
             tablahash_posicion(tabla, agenda[i]));
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Eliminar
  printf("\nEliminacion:\n");
  for (int i = 5; i > 2; --i) {
    printf("Eliminando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");
    tablahash_eliminar(tabla, agenda[i]);
  }

  // Buscar luego de eliminar
  printf("\nBusqueda luego de eliminar algunos contactos:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");

    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla (casilla %d).\n",
             tablahash_posicion(tabla, agenda[i]));
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Sobrescribir un contacto
  Contacto *nuevo = contacto_crear("Pepe Argento", "3410000000", 71);
  printf("\nSobrescribiendo el contacto: ");
  contacto_imprimir(agenda[0]);
  printf("\n\tpor: ");
  contacto_imprimir(nuevo);
  puts("");

  tablahash_insertar(tabla, nuevo);

  printf("Luego de sobrescribir, Pepe esta en casilla %d: ",
         tablahash_posicion(tabla, nuevo));

  Contacto *ret = tablahash_buscar(tabla, nuevo);
  contacto_imprimir(ret);
  puts("");

  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 6; ++i)
    contacto_destruir(agenda[i]);
  contacto_destruir(nuevo);

  return 0;
}
