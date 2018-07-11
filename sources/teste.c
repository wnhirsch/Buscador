#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#include "../headers/main.h"

#ifndef ABP_H 
#include "../headers/abp.h"
#endif

#ifndef LDE_H
#include "../headers/lde.h"
#endif

#ifndef LDEC_H
#include "../headers/lde_circular.h"
#endif

char *parse_string(char *str);

int LENGTH = 3;
char *mtr[3] = {"copa do mundo", "avl", "russia"};

int main(int args, char *argc[]){
	// estruturas do buscador:
	abp_node *abp_locais = NULL;

	//abp_node *termos = NULL;

	// lista com todas cosultas do arquivo, ordenada por frequência ascendente
	ldec_node *consultas_do_arquivo = NULL;

	char *entrada, *operacoes, *saida;
	FILE *file_entrada, *file_operacoes;
	int buffer_size = 255;
	char buffer[buffer_size];

	if(args < 3){
		printf("Does not have the right number of parameters\n");
		return 1;
	}

	entrada = argc[1];
	operacoes = argc[2];
	saida = argc[3];

	printf("Nome do arquivo de entrada: %s\n", entrada);
	printf("Nome do arquivo de operações: %s\n", operacoes);
	printf("Nome do arquivo de saida: %s\n", saida);
	
	// Open the files
	file_entrada = fopen(entrada, "r");
	file_operacoes = fopen(operacoes, "r");

	// Verifing if the files exist
	if(!file_entrada){
		printf("ERROR: The file of input does not exists\n");
		fclose(file_entrada);
		return 1;
	} else
	if (!file_operacoes){
		printf("ERROR: The file of operations does not exists");
		fclose(file_operacoes);
		return 1;
	}
	
	// reading the lines of the file of input
	printf("\nReading for file of input:\n");

	int i=0, MAX = 6;
	// lendo consultas
	while(!feof(file_entrada) && i++ < MAX){
		char *locality, *termo;
		// ldec_consulta: ldec dos termos da consulta atual
		// ldec do último termo inserido na ldec da consulta
		ldec_node *ldec_consulta = NULL, *termo_atual = NULL;

		fgets(buffer, buffer_size, file_entrada);

		// setting the strtok to get the locality and the terms between the tokens ";"
		locality = strtok(buffer, ";");
		termo = strtok(NULL, ";");
		
		printf("Parsing string\n");
		parse_string(locality);

		printf("Adicionando local '%s' a abp\n", locality);

		abp_node *abp_local_atual = abp_inserir_node(&abp_locais, locality);

		if(abp_local_atual->node == NULL){
			printf("Primeira vez buscado daqui\n");
		}
		else {
			printf("Já foi buscado daqui\n");
			printf("%s: ", abp_local_atual->chave);
		}

		while( termo != NULL ){
			parse_string(termo);

			// cria um novo termo e coloca no início da lista 
			termo_atual = ldec_insere_termo_alf(&ldec_consulta, termo);
			if(termo_atual != NULL){
				printf("termo atual: '%s'", termo_atual->chave);
			}

			termo = strtok(NULL, ";");
			printf("\nLDEC: ");
			ldec_imprime(ldec_consulta);
		}
		
		// ainda tem que ordenar as listas abaixo, por ordem de frequência
		ldec_node *consulta_inserida_no_local = insere_consulta_na_lista(&abp_local_atual->info, ldec_consulta);
		ldec_node *consulta_inserida_no_arquivo = insere_consulta_na_lista(&consultas_do_arquivo, ldec_consulta);

		//abp_local_atual->info = ldec_ordenada_frequencia(consultas_do_arquivo);

		printf("\nConsultas: \n");
		ldec_node *aux = consulta_inserida_no_arquivo;
		do {
			printf("%s[%d]: ", aux->chave, aux->frequencia);
			ldec_imprime(aux->info);	
			aux = aux->prox;
		} while(aux != consulta_inserida_no_arquivo);

		// !adicionar consulta a abp de localidades aqui 
		printf("\n\n");
	}

	imprime_abp(abp_locais, 0);
	return 0;
}

// parsing the string receives,
// all the characters to lower case
// if end the string with lineFeed, removes the lineFeed
char *parse_string(char *str){
	int len = strlen(str);
	int i;
	for(i=0; i<len; i++){
		//printf("\n[%d]: %c->",i, str[i]);
		
		str[i] = tolower(str[i]);
		
		switch(str[i]){
			case 10: // 10 = \n = Line Feed
				str[i] = 0;
				break;
			case -61:  // acentuação
				// case 'Á': 2 chars: [-61] e [-127]
				if(str[i+1] == -127){
					str[i] = 'a';	
					// shift the rest of the string 1 pra esquerda
					strncpy( (char*)(str+i+1),(char*)(str+i+2), len-i);
				} else // case 'ã': 2 chars [-61] e [-93]
				if(str[i+1] == -93){					
					// shift the rest of the string 1 pra esquerda
					str[i] = 'a';
					strncpy( (char*)(str+i+1),(char*)(str+i+2), len-i);
				} else // case 'é': 2 chars [-61] e [-93]
				if(str[i+1] == -87){					
					// shift the rest of the string 1 pra esquerda
					str[i] = 'e';
					strncpy( (char*)(str+i+1),(char*)(str+i+2), len-i);
				}
				break;
		}
		//printf("%1c[%d]\n",str[i],str[i]);
	}
	return str;
}
