/* Diogo Fouto Silva ist193705 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lista.h"

static list *lista; /* Lista duplamente ligada */


/* Inicializa a lista (head e last a NULL) */
void lista_init(void){

	lista = malloc(sizeof(list));

	lista->head = lista->last = NULL;
}


/* Insere um contacto no final da lista */
void add_as_last(contacto *new_node){

	if (lista->head == NULL) lista->head = lista->last = new_node;
	else {
		lista->last->next_lista = new_node;
		new_node->prev_lista = lista->last;
		lista->last = new_node;
	}
	lista->last->next_lista = NULL;
}


/* Faz print de todos os contactos presentes na lista */
void print_lista(void){

	contacto *aux;
	char *nome_aux, *token;
	const char delim[2] = "_1";

	for (aux = lista->head; aux != NULL; aux = aux->next_lista){

		nome_aux = malloc(strlen(aux->nome)+1);
		
		strcpy(nome_aux, aux->nome);
		token = strtok(nome_aux, delim);

		if (strcmp(aux->nome, token) == 0)
			print_contacto(aux);

		else
			printf("%s (%s) %s@%s %s\n", aux->nome, token, aux->email_local, aux->email_dominio, aux->telefone);

		free(nome_aux);
	}
}


/* Apaga um contacto da lista */
void delete_node(contacto *goner){

	/* Se a lista apenas contiver goner: */
	if (goner == lista->head && goner == lista->last) lista->head = lista->last = NULL;

	/* Se goner for a head da lista: */
	else if (goner == lista->head) lista->head = goner->next_lista;

	/* Se goner for o last da lista: */
	else if (goner == lista->last){
		lista->last = lista->last->prev_lista;
		lista->last->next_lista = NULL;
	}
	else {
		goner->prev_lista->next_lista = goner->next_lista;
		goner->next_lista->prev_lista = goner->prev_lista;
	}
}


/* Faz free de todos os contactos da lista e da lista em si */
void free_contactos_and_lista(void){

	contacto *aux;

	while (lista->head != NULL){

		aux = lista->head->next_lista;
		free_contacto(lista->head);
	 	lista->head = aux;
	}
	free(lista);
}