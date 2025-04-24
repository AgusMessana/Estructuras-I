#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int es_mayor_de(void *dato) {
  return contacto_es_mayor_de(dato, 60);
}

void *f_copia_contacto(void *dato) {
  return contacto_copia((Contacto *) dato);
}

void f_imprimir_contacto(void *dato) {
  contacto_imprimir((Contacto *) dato);
}

void f_dest_contacto(void *dato) {
  contacto_destruir((Contacto *) dato);
}

int main() {

  GList lista = glist_crear();
  Contacto *contactos[6];
  contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
  contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
  contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  for (int i = 0; i < 6; ++i) {
    lista = glist_agregar_inicio(lista, contactos[i], f_copia_contacto);
    contacto_destruir(contactos[i]);
  }

  printf("Lista:\n");
  glist_recorrer(lista, f_imprimir_contacto);

  GList mayores = glist_filtrar(lista, es_mayor_de, f_copia_contacto);

  printf("Lista filtrada:\n");
  glist_recorrer(mayores, f_imprimir_contacto);

  glist_destruir(lista, f_dest_contacto);
  glist_destruir(mayores, f_dest_contacto);

  return 0;
}
