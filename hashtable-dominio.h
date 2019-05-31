/* Diogo Fouto Silva ist193705 */

#include "contacto.h"

#ifndef HASHTABLE_DOMINIO_H
#define HASHTABLE_DOMINIO_H

/* Estrutura que guarda um dominio e o seu numero de ocorrencias */
typedef struct Dominio_X {
	char *dominio;
	int count;

	/* Ponteiro para proxima entrada da lista que e uma entrada na hashtable dos dominios */
	struct Dominio_X *next_ST_dom;
} dominio_x;


/* Funcoes Principais */
void ST_dom_init(void);
void ST_dom_insert(contacto *new);
int ST_dom_count(char *dominio);
void ST_dom_delete(contacto *dummy);
void ST_dom_free(void);

/* Auxiliar */
dominio_x *NEW_dom(const char *dominio);

#endif