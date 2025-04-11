#include "dlist.h"
#include <stdlib.h>

DList dlist_crear() {
    DList dlista;
    dlista.primero = NULL;
    dlista.ultimo = NULL;

    return dlista;
}

void dlist_destruir(DList* dlista) {
    DNodo* actual = dlista -> primero;
    while(actual != NULL) {
        DNodo* temp = actual;
        actual = actual -> sig;
        free(temp);
    }
    dlista->primero = NULL;
    dlista->ultimo = NULL;
}

int dlist_vacia(DList dlista) {
    if(dlista.primero == NULL && dlista.ultimo == NULL) {
        return 1;
    }
    
    return 0;
}

void dlist_recorrer(DList dlista, DListOrdenDeRecorrido orden, FuncionVisitante visit) {
    DNodo* temp;

    switch(orden) {
        case DLIST_RECORRIDO_HACIA_ADELANTE:
            for(temp = dlista.primero; temp != NULL; temp = temp->sig) {
                visit(temp->dato);
            }
            break;

        case DLIST_RECORRIDO_HACIA_ATRAS:
            for(temp = dlista.ultimo; temp != NULL; temp = temp->ant) {
                visit(temp->dato);
            }
            break;

        default:
            printf("Número de orden inválido.\n");
            break;
    }

    return;
}

DList dlist_agregar_final(DList dlista, int dato) {
    DNodo* nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo -> dato = dato;
    nuevoNodo -> sig = NULL;

    if(dlista.primero == NULL && dlista.ultimo == NULL) {
        nuevoNodo -> ant = NULL;
        dlista.primero = nuevoNodo;
        dlista.ultimo = nuevoNodo;

        return dlista;
    }

    nuevoNodo -> ant = dlista.ultimo;
    dlista.ultimo -> sig = nuevoNodo;
    dlista.ultimo = nuevoNodo;

    return dlista;
}

DList dlist_agregar_inicio(DList dlista, int dato) {
    DNodo* nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo -> dato = dato;
    nuevoNodo -> sig = dlista.primero;
    nuevoNodo -> ant = NULL;

    if(dlista.primero == NULL && dlista.ultimo == NULL) {
        dlista.primero = nuevoNodo;
        dlista.ultimo = nuevoNodo;

        return dlista;
    }

    dlista.primero -> ant = nuevoNodo;
    dlista.primero = nuevoNodo;

    return dlista;
}

int dlist_longitud (DList dlista) {
    int cont = 0;
    DNodo* temp = dlista.primero;
    for(; temp != NULL; temp = temp->sig) {
        cont++;
    }

    return cont;
}

void dlist_eliminar(DList* dlista, int pos) {
    if(dlista->primero == NULL && dlista->ultimo == NULL) {
        return;
    }
    if(pos == 0) {
        DNodo* temp = dlista->primero;
        dlista->primero = temp->sig;
        if(dlista->primero != NULL) {
            dlista->primero->ant = NULL;
        }
        else {
            dlista -> ultimo = NULL;
        }
        free(temp);

        return;
    }

    DNodo* temp = dlista->primero;
    for(int cont = 0; temp != NULL && cont != pos; temp = temp -> sig, cont++);

    if(temp == NULL) {
        return;
    }
    if (temp->ant != NULL) {
        temp->ant->sig = temp->sig;
    }
    if(temp->sig != NULL) {
        temp->sig->ant = temp->ant;
    }
    if(temp == dlista->ultimo) {
        dlista->ultimo = temp->ant;
    }
    free(temp);

    return;
}

