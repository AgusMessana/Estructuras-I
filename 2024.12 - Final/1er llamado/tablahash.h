#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear();


/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla.
 */
void tablahash_insertar(TablaHash tabla, const char *pal);

/**
 * Busca las palabras que empiezan por los primeros 3 caracteres dados
 */
void tablahash_buscar_prefijo(TablaHash tabla, const char *prefijo);

/**
 * Devuelve la cantidad de palabras que comienzan con la letra dada.
 */
unsigned tablahash_cant_por_letra(TablaHash tabla, const char letra);

/**
 * Elimina la palabra de la tabla si está, o disminuye su contador si ya estaba.
 */
void tablahash_eliminar(TablaHash tabla, const char *pal);

#endif                          /* __TABLAHASH_H__ */
