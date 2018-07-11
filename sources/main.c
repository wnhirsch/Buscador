// Bibliotecas Globais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

// Bibliotecas Locais
#include "../headers/AVL.h"
#include "../headers/LDC.h"
#include "../headers/operations.h"

// Constantes
#define BUFFER_SIZE 512

// Funções Auxiliares
char *strParse(char *str);

int main(int argc, char *argv[]){
	// Arvore de Localidades
	AVL *localidades = NULL; // para consultas
	AVL *locais_termos = NULL; // para termos

	// LDC - lista de consultas mais realizadas no arquivo
	LDC *consultas_arquivo = NULL;

	// Nome dos arquivos de entrada/saida
	char *entrada, *operacoes, *saida;
	// Ponteiro para arquivos
	FILE *file_entrada, *file_operacoes, *file_saida;
	char buffer[BUFFER_SIZE];

	// Verifica se os parametros foram informados corretamente
	if(argc < 4){
		printf("Does not have the right number of parameters\n");
		return -1;
	}

	// Armazena o nome dos arquios de entrada/saida
	entrada = argv[1];
	operacoes = argv[2];
	saida = argv[3];

	printf("Nome do arquivo de entrada: %s\n", entrada);
	printf("Nome do arquivo de operações: %s\n", operacoes);
	printf("Nome do arquivo de saida: %s\n", saida);

	// Abre os arquivos de entrada/saida
	file_entrada = fopen(entrada, "r");
	file_operacoes = fopen(operacoes, "r");
	file_saida = fopen(saida, "w");

	// Verifica a existencia dos arquivos
	if(!file_entrada){
		printf("ERROR: The file of input does not exists\n");
		fclose(file_entrada);
		return -2;
	}
	else if(!file_operacoes){
		printf("ERROR: The file of operations does not exists");
		fclose(file_operacoes);
		return -3;
	}
	else if(!file_operacoes){
		printf("ERROR: The file of output does not be created");
		fclose(file_saida);
		return -4;
	}

	printf("\nReading for file of input:\n");

	// Le todas as consultas do arquivo de entrada
	while(!feof(file_entrada)){
		char *strLocal = NULL;		// Nome da localidade
		char *strTermo = NULL;  	// Nome do Termo atual
		int isBalanced;	        	// Auxiliar para Inserção da AVL
		AVL *localAtual = NULL;		// Ponteiro para o nodo do local atual na AVL
		LDC *consultaAtual = NULL;	// Ponteiro para a consulta atual da localidade

		// Lemos uma linha do arquivo
		fgets(buffer, BUFFER_SIZE, file_entrada);

		// Lemos o nome da localidade e o primeiro termo
		strLocal = strtok(buffer, ";");
		strTermo = strtok(NULL, ";");

		if(strLocal != NULL && strTermo != NULL){
			// Simplificamos o nome da localidade
			printf("Parsing string\n");
			strParse(strLocal);

			printf("Adicionando local '%s' a AVL\n", strLocal);
			// Insere uma nova localidade na Arvore de locais
			localidades = insertAVL(localidades, strLocal, &isBalanced);
			// Busca o ponteiro inserido na Arvore
			localAtual = searchAVL(localidades, strLocal);

			// Insere uma nova localidade na árvore de locais dos termos
			locais_termos = insertAVL(locais_termos, strLocal, &isBalanced);

			// devolve a cidade
			AVL *local_termo = searchAVL(locais_termos, strLocal);

			// Enquanto não houver mais termos a serem lidos
			while(strTermo != NULL){
				// Simplifica o termo atual
				strParse(strTermo);
				// Adiciona o termos numa Lista de Termos auxiliar
				consultaAtual = insertFirstLDC(consultaAtual, strTermo, 1, NULL);

				// Insere o termo na lista global de termos de uma cidade
				local_termo->consultas = insertFirstLDC(local_termo->consultas, strTermo, 1, NULL);

				// Le outro termo
				strTermo = strtok(NULL, ";");
			}

			// Ordena essa Lista por Ordem ALfabetica para facilitar as operações
			consultaAtual = sortAlfLDC(consultaAtual);
			// Salva essa nova consulta na localidade atual
			localAtual->consultas = insertFirstLDC(localAtual->consultas, "", 1, consultaAtual);

			// Salva a nova consulta na lista de consultas geral do arquivo
			consultas_arquivo = insertFirstLDC(consultas_arquivo, "", 1, consultaAtual);

			// *DEBUGG*
			// LDC *aux = localAtual->consultas;
			// do{
			// 	show_all(aux->termos);
			// 	printf(" %d\n", aux->frequencia);
			// 	aux = aux->next;
			// }while(aux != localAtual->consultas);
			//
			// printf("\n");
			// printDotsReallyRB(localidades, 0);
			// printf("\n");
		}
	}

	printf("\nReading for file of operations:\n");

	while(!feof(file_operacoes)){
		char *strFunction;
		char *parameter1, *parameter2;

		// Lemos uma linha do arquivo
		fgets(buffer, BUFFER_SIZE, file_operacoes);

		// Lemos o a operação e os parametros
		strFunction = strtok(buffer, ";");
		parameter1 = strtok(NULL, ";");
		parameter2 = strtok(NULL, ";");

		printf("%s - %s - %s\n", strFunction, parameter1, parameter2);

		if(strFunction != NULL && !feof(file_operacoes)){
            printf("Executing operation '%c'\n", toupper(strFunction[0]));

			// Simplificamos os parametros
			strParse(parameter1);
			strParse(parameter2);

			// Verificamos qual operação é e a executamos
			switch(tolower(strFunction[0])){
				case 'a':
					operacaoA(localidades,file_saida,parameter1,atoi(parameter2));
				break;
				case 'b':
					printf("B[%d, %s]\n", atoi(parameter1), parameter2);
					operacaoB(consultas_arquivo, file_saida, atoi(parameter1));
				 	break;
				case 'c':
					printf("C[%s, %s, %s]\n", strFunction, parameter1, parameter2);
				 	operacaoC(locais_termos, file_saida, parameter1, atoi(parameter2));
				 	break;
				// case 'd':
				// 	operacaoD();
				// 	break;
				case 'e':
					operacaoE(localidades, file_saida, parameter1);
					break;
				case 'f':
					operacaoF(consultas_arquivo, file_saida);
					break;
				default:
					printf("Arquivo mal-formatado!");
				return -5;
			}
		}
	}

	// Fechamos os arquivos
	fclose(file_entrada);
	fclose(file_operacoes);
	fclose(file_saida);

	return 0;
}

// parsing the string receives,
// all the characters to lower case
// if end the string with lineFeed, removes the lineFeed
char *strParse(char *str){
    if (str == NULL)
        return str;

	int len = strlen(str);
	int i;
	for(i=0; i<len; i++){
		//printf("\n[%d]: %d->%c",i, str[i], str[i]);

		str[i] = tolower(str[i]);
		switch(str[i]){
			case 10: // 10 = \n = Line Feed
				str[i] = 0;
				break;
            case 13: // CR
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
