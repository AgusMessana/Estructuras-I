#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

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

void dlist_concatenar(DList* dlista1, DList dlista2) {
    if(dlista2.primero == NULL && dlista2.ultimo == NULL) {
        return;
    }
    if(dlista1->primero == NULL && dlista1 -> ultimo == NULL) {
        dlista1->primero = dlista2.primero;
        dlista1->ultimo = dlista2.ultimo;
        return;
    }

    dlista1->ultimo->sig = dlista2.primero;
    dlista2.primero->ant = dlista1->ultimo;
    dlista1->ultimo = dlista2.ultimo;
}

void dlist_insertar(DList* dlista, int dato, int pos) {
    DNodo* nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo -> dato = dato;

    if(dlista->primero == NULL && dlista->ultimo == NULL) {
        nuevoNodo->ant = NULL;
        nuevoNodo->sig = NULL;
        dlista->primero = nuevoNodo;
        dlista->ultimo = nuevoNodo;
        return;
    }
    if(pos == 0) {
        nuevoNodo->sig = dlista->primero;
        nuevoNodo->ant = NULL;
        dlista->primero->ant = nuevoNodo;
        dlista->primero = nuevoNodo;
        return;
    }

    DNodo* temp = dlista->primero;
    int cont = 0;
    for(; temp != NULL && cont != pos; temp = temp->sig, cont++);

    if(temp == NULL && cont != pos) {
        free(nuevoNodo);
        return;
    }
    if(temp == NULL && cont == pos) {
        nuevoNodo->sig = NULL;
        nuevoNodo->ant = dlista->ultimo;
        dlista->ultimo->sig = nuevoNodo;
        dlista->ultimo = nuevoNodo;
        return;
    }

    nuevoNodo->sig = temp;
    nuevoNodo->ant = temp->ant;
    temp->ant->sig = nuevoNodo;
    temp->ant = nuevoNodo;
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

int dlist_contiene(DList dlista, int dato) {
    DNodo* temp = dlista.primero;
    for(; temp != NULL; temp = temp->sig) {
        if(temp->dato == dato) {
            return 1;
        }
    }

    return 0;
}

int dlist_indice(DList dlista, int dato) {
    DNodo* temp = dlista.primero;
    int pos = 0;
    for(; temp != NULL && temp->dato != dato; temp = temp->sig, pos++);
    if(temp == NULL) {
        return -1;
    }
    return pos;
}

DList dlist_intersecar(DList dlista1, DList dlista2) {
    DList comunes = dlist_crear();
    if(dlista1.primero == NULL && dlista1.ultimo == NULL || dlista2.primero == NULL && dlista2.ultimo == NULL) {
        return comunes;
    }

    DNodo* temp1, *temp2;
    for(temp1 = dlista1.primero; temp1 != NULL; temp1 = temp1->sig ){
        int encontrado = 0;
        for(temp2 = dlista2.primero; temp2 != NULL && encontrado != 1; temp2 = temp2->sig) {
            if(temp1->dato == temp2->dato) {
                encontrado = 1;
            }
        }
        if(encontrado == 1) {
            comunes = dlist_agregar_inicio(comunes, temp1->dato);
        }
    }

    return comunes;
}

DList reverso(DList dlista) {
    DList reversa = dlist_crear();
    DNodo* temp = dlista.primero;

    for(; temp != NULL; temp = temp->sig) {
        reversa = dlist_agregar_inicio(reversa, temp->dato);
    }

    return reversa;
}