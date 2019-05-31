/* Diogo Fouto Silva ist193705 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contacto.h"
#include "hashtable-main.h"
#include "hashtable-dominio.h"
#include "lista.h"

#define NOMELEN 1024
#define EMAILLEN 512
#define TELEFONELEN 64


/* Funcoes Principais */
void power_on(void);
void power_off(void);
void novo_contacto(void);
void procura_contacto(void);
void apaga_contacto(void);
void altera_email(void);
void conta_dominio(void);

/* Funcoes Auxiliares */
void le_string(char *str);
void sort_email(char *email, char *email_local, char *email_dominio);


int main(){

	int comando;

	power_on();

	while ((comando = getchar()) != 'x'){

		switch (comando){
			case 'a':
				novo_contacto();
				break;
			case 'l': 
				print_lista(); /* A definicao desta funcao encontra-se em "lista.c" */
				break;
			case 'p':
				procura_contacto();
				break;
			case 'r':
				apaga_contacto();
				break;
			case 'e':
				altera_email();
				break;
			case 'c':
				conta_dominio();
				break;
		}
	}
	power_off();
	return 0;
}


/* Inicializa a lista duplamente ligada, a hashtable principal e a hashtable dos dominios */
void power_on(void){

	lista_init();
	ST_main_init();
	ST_dom_init();
}


/* Faz free de tudo (contactos, lista e hashtables) */
void power_off(void){

	ST_main_free();
	ST_dom_free();
	free_contactos_and_lista();
}
 
   
/* Cria um novo contacto e insere-o na lista e nas hashtables */
void novo_contacto(void){

	contacto *new;

	char nome[NOMELEN];
	char email[EMAILLEN];
	char email_local[EMAILLEN-1];  /* -1 para excluir caracter @ */
	char email_dominio[EMAILLEN-1];
	char telefone[TELEFONELEN];

	/* Le do input o nome, email e telefone */
	le_string(nome);
	le_string(email);
	le_string(telefone);

	/* Separa o email em email_local e email_dominio */
	sort_email(email, email_local, email_dominio);

	new = ST_main_search(nome); /* Verifica se o contacto a ser adicionado ja foi inserido */
	
	/* Se nao tiver na lista, entao cria contacto e insire na lista e nas hashtables */
	if (new == NULL){
		new = cria_contacto(nome, email_local, email_dominio, telefone);
		ST_main_insert(new);
		ST_dom_insert(new);
		add_as_last(new);
	}
}


/* Procura e faz print de um contacto */
void procura_contacto(void){

	contacto *con;

	char nome[NOMELEN];
	le_string(nome);

	con = ST_main_search(nome);

	/* Se o contacto existir, faz print */
	if (con != NULL) print_contacto(con);
	else printf("Nome inexistente.\n");
}


/* Apaga um contacto das hashtables e da lista */
void apaga_contacto(void){

	contacto *goner;

	char nome[NOMELEN];
	le_string(nome);

	goner = ST_main_search(nome);

	/* Se o contacto existir, apaga-o */
	if (goner != NULL){	
		ST_dom_delete(goner);
		ST_main_delete(goner);
		delete_node(goner);

		/* No fim, faz free dos atributos e do contacto em si */
		free_contacto(goner);
	}
	else printf("Nome inexistente.\n");
}


/* Altera o email de um contacto */
void altera_email(void){

	contacto *con;

	char nome[NOMELEN];
	char email[EMAILLEN]; 
	char email_local[EMAILLEN-1];
	char email_dominio[EMAILLEN-1];

	le_string(nome);
	le_string(email);
	sort_email(email, email_local, email_dominio);

	con = ST_main_search(nome);

	if (con != NULL){ 	/* Se o contacto existir: */

		/* Decrementa o contador do dominio antigo */
		ST_dom_delete(con);
		free(con->email_local); /* Faz free do email antigo */
		free(con->email_dominio);

		/* Aloca dinamicamente memoria para o novo email */
		con->email_local = malloc(strlen(email_local)+1);
		con->email_dominio = malloc(strlen(email_dominio)+1);

		/* Copia para o contacto con o email */
		strcpy(con->email_local, email_local);
		strcpy(con->email_dominio, email_dominio);

		/* Aumenta ou cria contador para o novo email do contacto con */
		ST_dom_insert(con);
	}
	else printf("Nome inexistente.\n");
}


/* Le o dominio do input, e faz print do seu numero de ocorrencias */
void conta_dominio(void){

	char email_dominio[EMAILLEN-1];

	le_string(email_dominio);

	printf("%s:%d\n", email_dominio, ST_dom_count(email_dominio));
}


/* Le uma string do input sem o espaco inicial */
void le_string(char *str){ scanf(" %s", str);}


/* Usando o strtok, separa email para email_local e email_dominio */
void sort_email(char *email, char *email_local, char *email_dominio){

	char *token;
	const char delim[2] = "@";
   	
	token = strtok(email, delim);
	strcpy(email_local, token);
    token = strtok(NULL, delim);
    strcpy(email_dominio, token);
}