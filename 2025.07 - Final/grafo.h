#ifndef __GRAFO_H__
#define __GRAFO_H__

/**
 * Estructura de la matriz de adyacencia esparsa.
 */
typedef struct {
  struct _Nodo **filas;
  int n;
} MatrizEsparsa;

/**
 * Crea una matriz esparsa
 */
MatrizEsparsa *matriz_crear(int n);

/**
 * Destruye una matriz esparsa
 */
void matriz_destruir(MatrizEsparsa * m);

/**
 * Inserta un 1 en la posición (i, j)
 */
void matriz_insertar(MatrizEsparsa * m, int i, int j);

/**
 * Elimina el 1 en la posición (i, j)
 */
void matriz_eliminar(MatrizEsparsa * m, int i, int j);

/**
 * Devuelve 1 si hay un 1 en (i, j) y 0 si no
 */
int matriz_contiene(MatrizEsparsa * m, int i, int j);

/**
 * Devuelve 1 si la matriz esparsa es simétrica y 0 si no
 */
int matriz_es_simetrica(MatrizEsparsa * m);

/**
 * Marca cada vecino de una fila
 */
void dfs (MatrizEsparsa *m, int u, int *visitado);

/**
 * Devuelve la cantidad de índices con los que se relaciona uno
 * dado, en uno o más pasos.
 */
int r_kleen(MatrizEsparsa * m, int indice);

#endif
