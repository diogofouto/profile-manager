/* Diogo Fouto Silva ist193705 */

#include "contacto.h"

#ifndef LISTA_H
#define LISTA_H

/* Estrutura que define a listaduplamente ligada onde vao ser inseridos os contactos */
typedef struct {
	/* head aponta para o primeiro elemento da lista, e last para o ultimo */
	contacto *head, *last;
} list;


/* Funcoes */
void lista_init(void);
void add_as_last(contacto *new_node);
void print_lista(void);
void delete_node(contacto *goner);
void free_contactos_and_lista(void);

#endif
