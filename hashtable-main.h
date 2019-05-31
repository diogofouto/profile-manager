/* Diogo Fouto Silva ist193705 */

#include "contacto.h"

#ifndef HASHTABLE_MAIN_H
#define HASHTABLE_MAIN_H

#define HASHLEN 1021  /* Tamanho das duas Hashtables */

/* Funcoes referentes a hashtable-main */
int hash(char *nome); /* A funcao hash e usada para as duas hashtables (main+dominios) */
void ST_main_init(void);
void ST_main_insert(contacto *new);
contacto *ST_main_search(char *nome);
void ST_main_delete(contacto *goner);
void ST_main_free(void);

#endif