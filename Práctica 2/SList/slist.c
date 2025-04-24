#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (; nodo->sig != NULL; nodo = nodo->sig);

  nodo->sig = nuevoNodo;

  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;

  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista) {
  int cont = 0;

  for (SNodo * temp = lista; temp != NULL; temp = temp->sig) {
    cont++;
  }

  return cont;
}

void slist_concatenar(SList * lista1, SList lista2) {
  if (*lista1 == NULL) {
    *lista1 = lista2;

    return;
  }

  SNodo *temp = *lista1;
  for (; temp->sig != NULL; temp = temp->sig);
  temp->sig = lista2;
}

void slist_insertar(SList * lista, int dato, int pos) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  if (*lista == NULL || pos == 0) {
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
    return;
  }

  SNodo *temp = *lista;
  for (int cont = 0; temp != NULL && cont < pos - 1; cont++) {
    temp = temp->sig;
  }

  if (temp == NULL) {
    free(nuevoNodo);
    return;
  }

  nuevoNodo->sig = temp->sig;
  temp->sig = nuevoNodo;
}

void slist_eliminar(SList * lista, int pos) {
  if (*lista == NULL) {
    return;
  }

  if (pos == 0) {
    SNodo *nodoAeliminar = *lista;
    *lista = (*lista)->sig;
    free(nodoAeliminar);
    return;
  }

  int cont;
  SList *temp = lista;
  for (cont = 0; cont != pos - 1 && (*temp)->sig; cont++, temp = &(*temp)->sig);

  if (*temp == NULL || (*temp)->sig == NULL) {
    return;
  }

  SNodo *nodoAeliminar = (*temp)->sig;
  (*temp)->sig = nodoAeliminar->sig;
  free(nodoAeliminar);

  return;
}

int slist_contiene(SList lista, int dato) {
  if (lista == NULL) {
    return 0;
  }

  SNodo *temp = lista;
  for (; temp->dato != dato && temp->sig != NULL; temp = temp->sig);
  if (temp->sig == NULL && temp->dato != dato) {
    return 0;
  }

  return 1;
}

int slist_indice(SList lista, int dato) {
  if (lista == NULL) {
    return -1;
  }

  int indice = 0;
  SNodo *temp = lista;
  while (temp != NULL) {
    if (temp->dato == dato) {
      return indice;
    }
    indice++;
    temp = temp->sig;
  }

  return -1;
}

SList slist_intersecar(SList lista1, SList lista2) {
  if (lista1 == NULL || lista2 == NULL) {
    return NULL;
  }

  SList comunes = slist_crear();
  SNodo *temp1, *temp2;
  for (temp1 = lista1; temp1 != NULL; temp1 = temp1->sig) {
    int encontrado = 0;
    for (temp2 = lista2; temp2 != NULL && encontrado != 1; temp2 = temp2->sig) {
      if (temp1->dato == temp2->dato) {
        encontrado = 1;
      }
    }
    if (encontrado == 1) {
      comunes = slist_agregar_inicio(comunes, temp1->dato);
    }
  }

  return comunes;
}

SList slist_intersecar_custom(SList lista1, SList lista2,
                              FuncionComparadora comp) {
  if (lista1 == NULL || lista2 == NULL) {
    return NULL;
  }

  SList comunes = slist_crear();
  SNodo *temp1, *temp2;
  for (temp1 = lista1; temp1 != NULL; temp1 = temp1->sig) {
    int encontrado = 0;
    for (temp2 = lista2; temp2 != NULL && encontrado != 1; temp2 = temp2->sig) {
      if (comp(temp1->dato, temp2->dato)) {
        encontrado = 1;
      }
    }
    if (encontrado) {
      comunes = slist_agregar_inicio(comunes, temp1->dato);
    }
  }

  return comunes;
}

SList slist_ordenar(SList lista, FuncionComparadora comp) {
  if (lista == NULL) {
    return NULL;
  }

  int ordenado = 0;
  while (ordenado == 0) {
    ordenado = 1;
    SNodo *actual = lista;
    while (actual->sig != NULL) {
      if (comp(actual->dato, actual->sig->dato) > 0) {
        int temp = actual->dato;
        actual->dato = actual->sig->dato;
        actual->sig->dato = temp;
        ordenado = 0;
      }
      actual = actual->sig;
    }
  }

  return lista;
}

SList reverso(SList lista) {
  if (lista == NULL) {
    return NULL;
  }

  SList reverse = slist_crear();
  SNodo *temp = lista;
  for (; temp != NULL; temp = temp->sig) {
    reverse = slist_agregar_inicio(reverse, temp->dato);
  }

  return reverse;
}

SList slist_intercalar(SList lista1, SList lista2) {
  SList intercalada = slist_crear();
  SNodo *temp1 = lista1, *temp2 = lista2;

  while (temp1 != NULL || temp2 != NULL) {
    if (temp1 != NULL) {
      intercalada = slist_agregar_final(intercalada, temp1->dato);
      temp1 = temp1->sig;
    }

    if (temp2 != NULL) {
      intercalada = slist_agregar_final(intercalada, temp2->dato);
      temp2 = temp2->sig;
    }
  }

  return intercalada;
}

SList *slist_partir2(SList lista) {
  SNodo *temp = lista;
  int len = slist_longitud(lista);

  for (int i = 0; i < (len - 1) / 2; i++, temp = temp->sig);

  SNodo *segunda_mitad = temp->sig;
  temp->sig = NULL;

  return segunda_mitad;
}
