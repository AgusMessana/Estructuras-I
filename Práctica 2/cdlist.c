#include "cdlist.h"
#include <stdlib.h>
#include <stdio.h>

CDList cdlist_crear() {
    CDList cdlista;
    cdlista.ultimo = NULL;
    return cdlista;
}

void cdlist_destruir(CDList* cdlista) {
    if(cdlista->ultimo == NULL) {
        return;
    }

    CDNodo* actual = cdlista->ultimo->sig;
    CDNodo* fin = cdlista->ultimo;
    while(actual != fin) {
        CDNodo* temp = actual;
        actual = actual->sig;
        free(temp);
    }
    free(fin);
    cdlista->ultimo = NULL;
}

int cdlist_vacia(CDList cdlista) {
    if(cdlista.ultimo == NULL) {
        return 1;
    }

    return 0;
}

void cdlist_recorrer(CDList cdlista, CDListOrdenDeRecorrido orden, FuncionVisitante visit) {
    if(cdlista.ultimo == NULL) {
        return;
    }

    CDNodo* temp;
    CDNodo* inicio;
    switch(orden) {
        case CDLIST_RECORRIDO_HACIA_ADELANTE:
            temp = cdlista.ultimo->sig;
            inicio = temp;
            int vuelta = 1;
            while(temp != inicio || temp == 1) {
                vuelta = 0;
                visit(temp->dato);
                temp = temp->sig;
            }
            break;

        case CDLIST_RECORRIDO_HACIA_ATRAS:
            temp = cdlista.ultimo;
            inicio = temp;
            int vuelta = 1;
            while(temp != inicio || temp == 1) {
                vuelta = 0;
                visit(temp->dato);
                temp = temp->ant;
        }
            break;
        
        default:
            printf("Número de orden inválido.\n");
            break;
    }
}

CDList cdlist_agregar_final(CDList cdlista, int dato) {
    
}