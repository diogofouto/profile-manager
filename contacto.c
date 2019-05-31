/* Diogo Fouto Silva ist193705 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contacto.h"


/* Cria e retorna variavel do tipo contacto */
contacto *cria_contacto(const char *nome, const char *email_local, const char *email_dominio, const char *telefone){
	
	contacto *new = malloc(sizeof(contacto)); /* Aloca memoria */
	
	/* Aloca dinamicamente apenas a memoria necessaria para os atributos do contacto new */
	new->nome = malloc(strlen(nome)+1);
	new->email_local = malloc(strlen(email_local)+1);
	new->email_dominio = malloc(strlen(email_dominio)+1);
	new->telefone = malloc(strlen(telefone)+1);

	/* Copia para new os argumentos da funcao */
	strcpy(new->nome, nome);
	strcpy(new->email_local, email_local);
	strcpy(new->email_dominio, email_dominio);
	strcpy(new->telefone, telefone);

	return new;
}


/* Faz print de um unico contacto */
void print_contacto(const contacto *con){
	printf("%s %s@%s %s\n", con->nome, con->email_local, con->email_dominio, con->telefone);
}


/* Faz free dos atributos do contacto e do contacto em si */
void free_contacto(contacto *con){

	free(con->nome);
	free(con->email_local);
	free(con->email_dominio);
	free(con->telefone);
	free(con);
}