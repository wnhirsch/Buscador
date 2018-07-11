#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LDEC_H
#include "../headers/lde_circular.h"
#endif

// Insere um termo no inicio da lista circular
// ordenada por frequencia
ldec_node *ldec_insere_termo(ldec_node *inicio, char *termo){
	ldec_node *novo;
	if(inicio != NULL){
		// o termo já existia, então apenas aumenta a frequencia
		novo = inicio;
	} else {
		// o nodo ainda não existia, deve ser criado
		novo = (ldec_node*)malloc(sizeof(ldec_node));
		if(!novo){
			printf("MEMORRY ERROR\n");
			return NULL;
		}
	}
	novo->chave = termo;
	return novo;
}

// Insere um termo em uma lista circular, 
// ordenada alfabeticamente
// retorna o nodo criado
ldec_node *ldec_insere_termo_alf(ldec_node **inicio, char *termo){
	ldec_node *novo = (ldec_node*)malloc(sizeof(ldec_node));
	ldec_node *comeco = *inicio; // ????
	
	novo->chave = (char *)malloc(sizeof(ldec_node));
	strcpy(novo->chave, termo);
	if(*inicio == NULL){
		novo->prox = novo;
		novo->ant = novo;
		*inicio = novo;
	} else {
		ldec_node *aux = comeco;
		// verificando se o termo deve ser o primeiro da lista
		if(strcmp(termo, aux->chave) < 1){
			novo->prox = aux;
			if(novo->prox == novo){
				novo->ant = aux;
				aux->prox = novo;
			
			} else {
				novo->ant = aux->ant;
				aux->ant->prox = novo;	
			}
			aux->ant = novo;
			*inicio = novo;
		} else {
			while(aux->prox != comeco && strcmp(termo, aux->prox->chave) == 1){				
				aux = aux->prox;
			}
			novo->prox = aux->prox;
			novo->ant = aux;
			aux->prox->ant = novo;
			aux->prox = novo;
		}
		
	}
	return novo;
}

/*ldec_node *insere_consulta(ldec_node *inicio, ldec_node *lista_termos){

}*/

ldec_node *insere_consulta_na_lista(ldec_node **lista, ldec_node *termos){
	ldec_node *inicio = *lista;
	ldec_node *aux=NULL, *novo = NULL;
	// primeira valor a ser colocado na lista
	if(inicio == NULL){
		novo = (ldec_node*)malloc(sizeof(ldec_node));
		*lista = novo;
		novo->prox = novo;
		novo->ant = novo;
	} else {
		// já existe um início
		aux = inicio;

		do {
			// verificando para cada nó, se ele contêm uma lista com os mesmos termos que os atuais
			if(ldec_cmp(aux->info, termos) == 0){
				aux->frequencia++;
				return aux;
			}
			aux = aux->prox;
		} while(aux != inicio);
		// novo nodo na lista
		novo = insere_no_inicio(inicio);
		*lista = novo;
	}
	novo->info = termos;
	novo->frequencia = 1;
	novo->chave = "consulta";
	return novo;
}

// insere uma consulta em uma lista de consultas de todo o arquivo
// ordena por ordem de frequência ascendente
ldec_node *insere_consulta_no_universo(ldec_node **inicio, ldec_node *termos);

// insere no início da lista dada.
// e retorna o novo início da lista
// ! não seta nenhuma informação
// também pode ser visto como uma inserção antes do nodo início dado
ldec_node *insere_no_inicio(ldec_node *inicio){
	ldec_node *novo = (ldec_node*)malloc(sizeof(ldec_node));
	
	if(inicio == NULL){
		// não há nenhum item na lista
		novo->prox = novo;
		novo->ant = novo;
	} else
	if(inicio == inicio->prox){
		// há apenas um item na lista
		novo->prox = inicio;
		novo->ant = inicio;

		inicio->prox = novo;
		inicio->ant = novo;
	} else {
		// há mais de um item na lista
		novo->ant = inicio->ant;
		novo->prox = inicio;

		novo->ant->prox = novo;
		inicio->ant = novo;
	}
	return novo;
}

// compara duas listas circulares, se forem iguais, retorna 0,
// se a primeira for menor, retorna -1,
// se a primeira for maior, retorna 1
int ldec_cmp(ldec_node *nodeA, ldec_node *nodeB){
	ldec_node *auxA = nodeA, *auxB = nodeB;
	// comparando se as duas listas existem
	if(auxA != NULL && auxB == NULL){
		return 1;
	} else
	if(auxA == NULL && auxB != NULL){
		return -1;
	} else {
		int res_cmp;

		do {
			// comparando cada um dos nodos de cada uma das lista, pra
			// vendo se são iguais
			res_cmp = strcmp(auxA->chave, auxB->chave);
			if(res_cmp != 0){
				return res_cmp;
			} 
			auxA = auxA->prox;
			auxB = auxB->prox;
		} while(nodeA != auxA && nodeB != auxB);

		if(res_cmp == 0 && nodeA == auxA && nodeB == auxB){
			// as duas listas são exatamente iguais
			return 0;
		} else
		if(nodeA == auxA){
			// a primeira lista chegou no início novamente
			return -1;
		} else 
		if(nodeB == auxB){
			// a segunda lista chegou no início novamente
			return 1;
		} else {
			// as duas listas tem o mesmo tamanho
			// retorna a última comparação
			return res_cmp;
		}
	}
}

ldec_node *ldec_ordenada_frequencia(ldec_node *lista){
	// nothing for while
	return lista;
}

void ldec_imprime(ldec_node *inicio){
	ldec_node *aux = inicio;
	if(aux != NULL){
		printf("%s->", aux->chave);
		aux = aux->prox;
		while(aux != inicio){
			printf("%s->", aux->chave);
			aux = aux->prox;
		}
	} else {
		printf("NULL");
	}
	printf("\n");
}