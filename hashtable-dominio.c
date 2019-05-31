/* Diogo Fouto Silva ist193705 */

#include <stdlib.h>
#include <string.h>

#include "hashtable-dominio.h"
#include "hashtable-main.h"

static dominio_x **dom_heads; /* Hashtable por Encadeamento Externo */


/* Inicializa a hashtable dos dominios a NULL */
void ST_dom_init(void){

	int i;
	dom_heads = malloc(HASHLEN * sizeof(dominio_x*));

	for (i = 0; i < HASHLEN; i++) dom_heads[i] = NULL;
}


/*Cria e retorna variavel do tipo dominio_x */
dominio_x *NEW_dom(const char *dominio){
	
	dominio_x *x = malloc(sizeof(dominio_x)); /* Aloca memoria */

	/* Aloca apenas memoria necessaria para o dominio */
	x->dominio = malloc(strlen(dominio)+1);

	/* Copia para x o argumento da funcao */
	strcpy(x->dominio, dominio);

	/* Contador do novo dominio comeca a 1 */
	x->count = 1;
	return x;
}


/* Aumenta o contador se o dominio de new ja se encontrar na hashtable
   Caso contrario, cria variavel que contenha esse dominio e adiciona-a a hashtable */
void ST_dom_insert(contacto *new){

	dominio_x *aux;
	int i = hash(new->email_dominio);

	for (aux = dom_heads[i]; aux != NULL; aux = aux->next_ST_dom){

		/* Se o dominio de new ja se encontrar la: */
		if (strcmp(aux->dominio, new->email_dominio) == 0){
			aux->count++;
			return;
		}
	}
	/* Caso contrario: */
	aux = NEW_dom(new->email_dominio);
	aux->next_ST_dom = dom_heads[i];
	dom_heads[i] = aux;
}


/* Decrementa o contador do dominio do contacto a ser apagado */
void ST_dom_delete(contacto *dummy){

	dominio_x *aux;
	int i = hash(dummy->email_dominio);

	for (aux = dom_heads[i]; aux != NULL; aux = aux->next_ST_dom)
		if (strcmp(aux->dominio, dummy->email_dominio) == 0) aux->count--;
}


/* Devolve o numero de ocorrencias do dominio */
int ST_dom_count(char *dominio){

	dominio_x *aux; 
	int i = hash(dominio);

	for (aux = dom_heads[i]; aux != NULL; aux = aux->next_ST_dom){

		if (strcmp(aux->dominio, dominio) == 0) return aux->count;
	}
	/* Se o dominio nao tiver sido inserido: */
	return 0;
}


/* Faz free de todas as entradas da hashtable e da hashtable em si */
void ST_dom_free(void){ 

	int i;
	dominio_x *aux, *aux_2;

	for (i = 0; i < HASHLEN; i++)
		for (aux = dom_heads[i]; aux != NULL; ){

			aux_2 = aux;
			aux = aux->next_ST_dom;
			free(aux_2->dominio);
			free(aux_2);
		}
	free(dom_heads);
}