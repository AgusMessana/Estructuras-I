#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "2do_parcial_2023.h"

GList glist_crear() {
  GList lista;
  lista.primero = NULL;
  lista.ultimo = NULL;
  return lista;
}

GList glist_agregar_final(GList lista, void *dato, FuncionCopia copia) {
  GNodo *nuevo = malloc(sizeof(GNodo));
  nuevo->dato = copia(dato);
  nuevo->sig = NULL;
  if (lista.primero == NULL)
    lista.primero = nuevo;
  else
    lista.ultimo->sig = nuevo;
  lista.ultimo = nuevo;
  return lista;
}

void glist_destruir(GList lista, FuncionDestructora destroy) {
  GNodo *temp;
  for (GNodo * nodo = lista.primero; nodo != NULL;) {
    temp = nodo;
    nodo = nodo->sig;
    destroy(temp->dato);
    free(temp);
  }
}

void glist_recorrer(GList lista, FuncionVisitante visit) {
  for (GNodo * nodo = lista.primero; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

GList glist_map(GList lista, FuncionTransformar f, FuncionCopia c) {
  GList listaMap = glist_crear();

  for (GNodo * temp = lista.primero; temp != NULL; temp = temp->sig) {
    listaMap = glist_agregar_final(listaMap, f(temp->dato), c);
  }

  return listaMap;
}

void *stringMayuscula(void *dato) {
  char *palabra = (char *) dato;
  int len = strlen(palabra);
  char *mayus = (char *) malloc((len + 1) * sizeof(char));

  for (int i = 0; i < len; i++) {
    mayus[i] = toupper(palabra[i]);
  }
  mayus[len] = '\0';

  return mayus;
}

void *copia_string(void *dato) {
  char *str = (char *) dato;
  char *nuevo = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(nuevo, str);
  return nuevo;
}

void dest_string(void *dato) {
  free(dato);
}

void imprimir(void *dato) {
  char *str = (char *) dato;
  printf("%s", str);
}

int main() {
  GList lista = glist_crear();
  char *str = " Licenciatura ";
  lista = glist_agregar_final(lista, str, copia_string);
  str = "en ";
  lista = glist_agregar_final(lista, str, copia_string);
  str = " Ciencias ";
  lista = glist_agregar_final(lista, str, copia_string);
  str = "de la ";
  lista = glist_agregar_final(lista, str, copia_string);
  str = " Computacion .";
  lista = glist_agregar_final(lista, str, copia_string);

  printf("Lista original:\n");
  glist_recorrer(lista, imprimir);
  GList listaMayus = glist_map(lista, stringMayuscula, copia_string);
  printf("\n");
  printf("Lista en mayuscula:\n");
  glist_recorrer(listaMayus, imprimir);
  printf("\n");

  glist_destruir(lista, dest_string);
  glist_destruir(listaMayus, dest_string);
  return 0;
}
