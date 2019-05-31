/* Diogo Fouto Silva ist193705 */

#include <stdlib.h>
#include <string.h>

#include "hashtable-main.h"

static contacto **main_heads; /* Hashtable por encadeamento externo */


/* Funcao hash:
	Calcula uma soma ponderada dos caracteres
	Soma e feita com modulo
	HASHLEN e primo, para minimizar colisoes
	Recalcula a base em cada iteracao
	Evita anomalias com chaves altamente regulares
*/
int hash(char *nome){

	int h, a = 31415, b = 27183;

	for (h = 0; *nome != '\0'; nome++, a = a*b % (HASHLEN-1))
		h = (a*h + *nome) % HASHLEN;

	return h;
}


/* Inicializa a hashtable main a NULL */
void ST_main_init(void){

	int i; 
	main_heads = malloc(HASHLEN * sizeof(contacto*));

	for (i = 0; i < HASHLEN; i++) main_heads[i] = NULL;
}


/* Insere novo contacto como head da lista com indice i calculado por hash */
void ST_main_insert(contacto *new){

	int i = hash(new->nome);

	new->next_ST_main = main_heads[i];
	if (main_heads[i] != NULL) main_heads[i]->prev_ST_main = new;
	main_heads[i] = new;
}


/* Procura pelo nome e devolve contacto que corresponde a esse nome */
contacto *ST_main_search(char *nome){

	contacto *aux;
	int i = hash(nome);

	for (aux = main_heads[i]; aux != NULL; aux = aux->next_ST_main)
		if (strcmp(aux->nome, nome) == 0) return aux;

	/* Se nao encontrar, devolve NULL */
	return NULL;
}


/* Apaga da hashtable contacto goner */
void ST_main_delete(contacto *goner){
	
	int i = hash(goner->nome);

	/* Se goner for a head */
	if (goner == main_heads[i]) main_heads[i] = goner->next_ST_main;

	/* Se goner for o ultimo da lista */
	else if (goner->next_ST_main == NULL){
		goner->prev_ST_main->next_ST_main = NULL;
	}
	else {
		goner->prev_ST_main->next_ST_main = goner->next_ST_main;
		goner->next_ST_main->prev_ST_main = goner->prev_ST_main;
	}
}


/* Faz free apenas da hashtable */
void ST_main_free(void){ free(main_heads); }