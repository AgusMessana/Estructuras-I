#include "slist1.h"
#include <stdlib.h>

SList slist_crear() {
    SList lista;
    lista.primero = NULL;
    lista.ultimo = NULL;

    return lista;
}

SList slist_agregar_final(SList lista, int dato) {
    SNodo* nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo -> dato = dato;
    nuevoNodo -> sig = NULL;

    if(lista.ultimo != NULL) { // si lista.ultimo == NULL, la lista es vacía
        lista.ultimo -> sig = nuevoNodo;
    }
    else {
        lista.primero = nuevoNodo; // si la lista es vacía, el primer elemento será el nuevo nodo
    }
    lista.ultimo = nuevoNodo; // ahora el último elemento es el nuevo nodo

    return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
    SNodo* nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo -> dato = dato;
    nuevoNodo -> sig = lista.primero;
    lista.primero = nuevoNodo;

    if(lista.ultimo == NULL) {
        lista.ultimo = nuevoNodo;
    }

    return lista;
}

// La ventaja principal es que resulta más sencillo y eficiente agregar elementos al final de la lista ya que tenemos un puntero al último elemento de ella. Por el lado de las desventajas, ocupa un poco más de espacio en la memoria.