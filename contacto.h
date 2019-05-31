/* Diogo Fouto Silva ist193705 */

#ifndef CONTACTO_H
#define CONTACTO_H

/* Estrutura principal do contacto */
typedef struct Contacto {

	char *nome;
	char *email_local;
	char *email_dominio;
	char *telefone;

	/* Ponteiros para next e previous da lista e da hashtable main */
	struct Contacto *next_lista;
	struct Contacto *prev_lista;
	struct Contacto *next_ST_main;
	struct Contacto *prev_ST_main;
} contacto;


/* Funcoes */
contacto *cria_contacto(const char *nome, const char *email_local, const char *email_dominio, const char *telefone);
void print_contacto(const contacto *con);
void free_contacto(contacto *con);

#endif

/* Nota: A hashtable-main e a lista tem como elementos pointers do tipo contacto */