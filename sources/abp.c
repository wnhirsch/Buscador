#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/abp.h"

#ifndef TIPOCONSULTA_H
#include "../headers/tipoconsulta.h"
#endif

//abp_node *inserir_abp_node(abp_node **inicio, char *info){
abp_node *abp_inserir_node(abp_node **inicio, char *info){
	abp_node *novo;
	abp_node *atual = *inicio;
	printf("Inserindo '%s' na abp\n", info);

	if(!atual){
		printf("Criando nodo central\n");
		novo = (abp_node *)malloc(sizeof(abp_node));
		if(!novo){
			printf("Error in allocating memory\n");
			return NULL;
		}
		*inicio = novo;
	} else {
		abp_node *aux = atual;
		int res_cmp = strcmp(info, aux->chave);
		if(res_cmp == 0){
			aux->frequencia++;
			return aux;
		} else
		if(res_cmp < 0){
			printf("Menor - ");
			if(aux->esq != NULL){
				return abp_inserir_node(&aux->esq, info);
			}
			else {
				printf("Criando nodo esq\n");
				novo = (abp_node *)malloc(sizeof(abp_node));
				aux->esq = novo;
			}
		} else {
			printf("Maior - ");
			if(aux->dir != NULL){
				return abp_inserir_node(&aux->dir, info);	
			}
			else {
				printf("Criando nodo dir\n");
				novo = (abp_node *)malloc(sizeof(abp_node));
				aux->dir = novo;
			}

		}
	}
	printf("Setando nodo\n");
	novo->chave = (char*)malloc(sizeof(char)*(strlen(info)+1));
	if(!novo->chave){
		printf("Error allocating memory\n");
		return NULL;
	}
	strcpy(novo->chave, info);
	novo->frequencia = 1;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->node = NULL;
	novo->lde_cidade = NULL;
	novo->info = NULL;
	return novo;
}


// procura na árvore pela chave informada. se encontrar.
abp_node *abp_procurar_chave(abp_node *raiz, char *info){
	if(raiz == NULL){
		printf("Nodo não encontrado\n");
		return NULL;
	}

	int res_cmp = strcmp(info, raiz->chave);

	if(res_cmp == 0){
		return raiz;
	} else
	if(res_cmp < 0){
		return abp_procurar_chave(raiz->esq, info);
	} else {
		return abp_procurar_chave(raiz->dir, info);
	}
}

//
abp_node *abp_insere_termo(abp_node *raiz, char *info){
	if(raiz == NULL){
		raiz = (abp_node*)malloc(sizeof(abp_node));
	}
	else {
		if(strcmp(info, raiz->chave) < 0){
			raiz->esq = abp_insere_termo(raiz->esq, info);
		} else {
			raiz->dir = abp_insere_termo(raiz->dir, info);
		}
	}
	return raiz;
}


// procura uma consulta na abp. se não encontrar, cria um nodo com aquela consulta
// retorna sempre a raiz da árvore ou sub-árvore
abp_node *abp_insere_consulta(abp_node *raiz, LDE_Node *termos){
	if(raiz == NULL){
		printf("É uma nova consulta\n");
		raiz = (abp_node*)malloc(sizeof(abp_node));
		raiz->frequencia = 1;
		raiz->esq = NULL;
		raiz->dir = NULL;
		raiz->chave = NULL;
		raiz->node = termos;
		raiz->info = NULL;
	} else {
		imprime_lde_linha(raiz->node);
		LDE_Node *lista = raiz->node, *nova_lista = termos;
		// verifica até o final da lista se os dois nodos são iguais
		while(lista != NULL && nova_lista != NULL && strcmp(lista->info, nova_lista->info) == 0){
			lista = lista->prox;
			nova_lista = nova_lista->prox;
		}
		if(lista == nova_lista){
			printf("=");
			printf("As duas listas de termos são iguais");
			raiz->frequencia = raiz->frequencia +1;
			return raiz;
			// TODO: reordena lde ordenada pela frequencia
		} else {
			// as duas listas são diferentes, porque ??
			// comparação de tamanho
			if(lista == NULL){
				printf("1");
				// a nova_lista é maior que a lista na abp
				raiz->dir = abp_insere_consulta(raiz->dir, termos);
			} else
			if(nova_lista == NULL){
				printf("2");
				// a nova_lista é menor que a lista na abp
				raiz->esq = abp_insere_consulta(raiz->esq, termos);
			} else {
				// comparação do elemento diferente
				int res_cmp = strcmp(nova_lista->info, lista->info);	
				if(res_cmp < 0){
					printf("3");
					// o elem da nova_lista é menor que o elem da lista da abp
					raiz->esq = abp_insere_consulta(raiz->esq, termos);
				} else {
					printf("4");
					// o elem da nova_lista é maior
					raiz->dir = abp_insere_consulta(raiz->dir, termos);
				}
			}
		}
	}
	return raiz;
}

// procura uma consulta na abp. se não encontrar, cria um nodo com aquela consulta
// retorna o último nodo adicionado a árvore
abp_node *abp_insere_consulta2(abp_node **inicio, LDE_Node *termos){
	abp_node *raiz = *inicio;
	if(raiz == NULL){
		printf("É uma nova consulta\n");
		raiz = (abp_node*)malloc(sizeof(abp_node));
		raiz->frequencia = 1;
		raiz->esq = NULL;
		raiz->dir = NULL;
		raiz->chave = NULL;
		raiz->node = termos;
		raiz->info = NULL;
		raiz->consultas = NULL;
		*inicio = raiz;
	} else {
		imprime_lde_linha(raiz->node);
		LDE_Node *lista = raiz->node, *nova_lista = termos;
		// verifica até o final da lista se os dois nodos são iguais
		while(lista != NULL && nova_lista != NULL && strcmp(lista->info, nova_lista->info) == 0){
			lista = lista->prox;
			nova_lista = nova_lista->prox;
		}
		if(lista == nova_lista){
			printf("=");
			printf("As duas listas de termos são iguais");
			raiz->frequencia = raiz->frequencia +1;
			return raiz;
			// TODO: reordena lde ordenada pela frequencia
		} else {
			// as duas listas são diferentes, porque ??
			// comparação de tamanho
			if(lista == NULL){
				printf("1");
				// a nova_lista é maior que a lista na abp
				raiz = abp_insere_consulta(raiz->dir, termos);
			} else
			if(nova_lista == NULL){
				printf("2");
				// a nova_lista é menor que a lista na abp
				raiz = abp_insere_consulta(raiz->esq, termos);
			} else {
				// comparação do elemento diferente
				int res_cmp = strcmp(nova_lista->info, lista->info);	
				if(res_cmp < 0){
					printf("3");
					// o elem da nova_lista é menor que o elem da lista da abp
					raiz = abp_insere_consulta(raiz->esq, termos);
				} else {
					printf("4");
					// o elem da nova_lista é maior
					raiz = abp_insere_consulta(raiz->dir, termos);
				}
			}
		}
	}
	return raiz;
}



void imprime_abp(abp_node *inicio, int height){
	if(inicio){
		int i;
		for(i=0; i<height; i++)
			printf("--");

		printf("%s - %d\n", inicio->chave, inicio->frequencia);
		imprime_abp(inicio->esq, i+1);
		imprime_abp(inicio->dir, i+1);
	}
	
}

void imprime_abp_consulta(abp_node *inicio, int height){
	if(inicio){
		int i;
		for(i=0; i<height; i++)
			printf("--");
		printf("%d ", inicio->frequencia);
		imprime_lde_linha(inicio->node);
		imprime_abp_consulta(inicio->esq, height+1);
		imprime_abp_consulta(inicio->dir, height+1);
	}
}