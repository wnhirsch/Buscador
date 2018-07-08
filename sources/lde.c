#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/lde.h"

// Functions
LDE_Node* inicializa_LDE_Node(){
	return NULL;
}

// Insere um Node na lista por ordem alfabetica
// retorna o nodo adicionado
LDE_Node* insere_info_LDE_Node_alt(LDE_Node* inicio, char *info){
	LDE_Node *novo = NULL;
	if(inicio == NULL){
		novo = (LDE_Node *)malloc(sizeof(LDE_Node));
		novo->info = info;
		novo->prox = NULL;
		novo->ant = NULL;
		return novo;
	} else {
		LDE_Node* na_lista = procura_LDE_Node(inicio, info);
		if(na_lista != NULL){
			// termo já está na lista
			na_lista->frequencia++;
			novo = na_lista;
			// TODO: ordena uma lista por lista por frequência ??
		} else {
			// termo não está na lista
			novo = (LDE_Node *)malloc(sizeof(LDE_Node));
			if(novo == NULL){
				printf("ERROR in the allocation of memory\n");
				return NULL;
			}
			novo->info = info;
		}
	}
	return novo;
}

// Tudo isso pra não precisar percorrer duas vezes a lista !!!!

// verifica se a string info já está na lista e verifica sua posição alfabeticamente
// pode retornar o nodo onde info está OU
// se info não estiver na lista retorna
// OU NULL se for pra colocar no início da lista
// OU LDE_Node que é maior que o que está sendo criado
LDE_Node* procura_LDE_Node_alphabetic(LDE_Node* inicio, char *info){
	if(inicio == NULL){
		printf("Lista vazia");
		return NULL;
	} 
	// verifica se o info é menor que o primeiro nodo
	if(strcmp(info, inicio->info) < 0){
		return NULL;
	}

	// verifica se o atual vem antes do atual
	LDE_Node* atual = inicio;
	while(strcmp(info, atual->info) > 0 ){
		atual = atual->prox;
	}
	return atual;
}

// verifica se o nodo já está na lista
// organizada por ordem de frequencia (TODO e depois por ordem alfabetica)
// retorna o nodo da lista que estava procurando ou o último nodo da lista
LDE_Node* procura_LDE_Node(LDE_Node* inicio, char *info){
	if(inicio == NULL){
		printf("Lista vazia");
		return NULL;
	} 
	// verifica se o info é menor que o primeiro nodo
	if(strcmp(info, inicio->info) < 0){
		return NULL;
	}

	// verifica se o atual vem antes do atual
	LDE_Node* atual = inicio;
	if(atual->prox == NULL) printf("Proximo é NULL\n");
	while(atual->prox != NULL && strcmp(info, atual->prox->info) > 0 ){
		atual = atual->prox;
	}
	return atual;
}


// Insere um Node na lista por ordem de frequência
// retorna o início da lista
//LDE_Node* insere_info_LDE_Node(LDE_Node* inicio, char *info){
LDE_Node* insere_info_LDE_Node_alf(LDE_Node **lista, char *info){
	LDE_Node *novo, *inicio = *lista;

	printf("LDE - inserindo '%s' len(%d) na lista\n", info, strlen(info));
	if(inicio == NULL){
		printf("A lista está vazia\n");
		novo = (LDE_Node *)malloc(sizeof(LDE_Node));
		if(!novo)	return NULL;
		novo->info = (char *)malloc(sizeof(char)*(strlen(info)+1));
		strcpy(novo->info, info);
		novo->prox = NULL;
		novo->ant = NULL;
		novo->frequencia = 1;
		*lista = novo;
	} else {
		// coloca ou no início da lista
		// ou após o nodo encontrado por procura_LDE_Node
		LDE_Node* na_lista = procura_LDE_Node(inicio, info);
		// retorno vazio, tem que colocar no início na lista
		if(na_lista == NULL){
			printf("Inserindo no início\n");
			novo = (LDE_Node *)malloc(sizeof(LDE_Node));
			if(novo == NULL){
				printf("ERROR in the allocation of memory\n");
				return NULL;
			}
			novo->info = (char *)malloc(sizeof(char)*(strlen(info)+1));
			strcpy(novo->info, info);
			novo->frequencia = 1;
			novo->ant = NULL;
			novo->prox = inicio;
			inicio->ant = novo;
			*lista = novo;
		} else if(na_lista->prox && strcmp(info, na_lista->prox->info) == 0){
			// verifica se o nodo atual é igual ao procurado
			printf("%s já está na lista - [%d++]\n", info, na_lista->prox->frequencia);
			na_lista->prox->frequencia = na_lista->prox->frequencia + 1;
			// TODO: ordena a lista por lista por frequência ??
			novo = na_lista->prox;
		} else {
			printf("Colocando após %s\n", na_lista->info);
			// termo não está na lista
			novo = (LDE_Node *)malloc(sizeof(LDE_Node));
			if(novo == NULL){
				printf("ERROR in the allocation of memory\n");
				return NULL;
			}
			novo->info = (char *)malloc(sizeof(char)*(strlen(info)+1));
			strcpy(novo->info, info);
			novo->frequencia = 1;

			novo->prox = na_lista->prox;
			novo->ant = na_lista;
			if(na_lista->prox)
				na_lista->prox->ant = novo;
			na_lista->prox = novo;
		}
	}
	return novo;
}





// CERTO


// Funções com descritor
lde_descritor* inicializa_lde_descritor(){
	lde_descritor* descritor = (lde_descritor*)malloc(sizeof(lde_descritor));
	descritor->inicio = NULL;
	descritor->fim = NULL;
	return descritor;
}

/*
PSEUDO-CÓDIGO

Insere algo na abp. e retorna o nodo da da abp.
se não tiver, cria nodo na abp, retorna o nodo da abp
se o nodo da abp não tiver um nodo lde nele,
cria o nodo lde e insere no início da lista.
senão, frequencia+1 no nodo da lde, ( ponteiro pro int da abp ?)
e reordena a lde por frequência

*/
// ordenado por frequencia
LDE_Node *insere_termo_lde(lde_descritor* descritor, LDE_Node *nodo, char *info){
	// Se o nodo dentro da abp estiver vazio, então é a primeira inserção do nodo
	if(nodo == NULL){
		nodo = insere_info_lde_inicio(descritor, info);
		printf("termo: '%s' - frequencia %d\n", nodo->info, nodo->frequencia);
	} else {
		// node == info
		nodo->frequencia = nodo->frequencia + 1;
		printf("termo: '%s' - nodo '%s' - frequencia %d\n", info, nodo->info, nodo->frequencia);
		// reorganizado lde
		LDE_Node *nodo_anterior = remove_lde_node(descritor, nodo);
		insere_lde_frequencia(descritor, nodo_anterior, nodo);
	}
	return nodo;
}


// ! Ideia - copiar o conteúdo da string primeiro, e depois enviar pra função
// Ordenar por frequência ( talvez por alfabeticamente dentro ?)
// ordenada com inicio < fim
// retorno o nodo que coloca na lista
LDE_Node *insere_info_lde_inicio(lde_descritor* original_descritor, char *info){
	lde_descritor *descritor = original_descritor;
	LDE_Node* inicio = descritor->inicio;
	LDE_Node* novo = (LDE_Node*)malloc(sizeof(LDE_Node));

	novo->frequencia = 1;
	novo->info = (char *)malloc(sizeof(char)+1);
	strcpy(novo->info, info);

	novo->ant = NULL;
	
	if(inicio == NULL){
		novo->prox = NULL;

		descritor->inicio = novo;
		descritor->fim = novo;
	} else {
		novo->prox = inicio;
		inicio->ant = novo;
		descritor->inicio = novo;
	}
	return novo;
}


LDE_Node *insere_consulta_lde(lde_descritor* descritor, LDE_Node *abp_origem_consulta, LDE_Node *consulta){
	// Se o nodo dentro da abp estiver vazio, então é a primeira inserção do nodo
	if(abp_origem_consulta == NULL){
		// insere no início da lista
		printf("Novo node\n");
		abp_origem_consulta = insere_consulta_lde_inicio(descritor, consulta);
		imprime_lde_linha(consulta);
		printf("- frequencia %d\n", consulta->frequencia);

	} else {
		// node == info
		abp_origem_consulta->frequencia = abp_origem_consulta->frequencia + 1;
		imprime_lde_linha(consulta);
		printf("- frequencia %d\n", consulta->frequencia);
		// reorganizado lde
		LDE_Node *lista_anterior = remove_lde_node(descritor, abp_origem_consulta);
		insere_lde_frequencia(descritor, lista_anterior, abp_origem_consulta);
	}
	return abp_origem_consulta;
}

// ! Ideia - copiar o conteúdo da string primeiro, e depois enviar pra função
// Ordenar por frequência ( talvez por alfabeticamente dentro ?)
// ordenada com inicio < fim
// retorno o nodo que coloca na lista
LDE_Node *insere_consulta_lde_inicio(lde_descritor* original_descritor, LDE_Node *node){
	lde_descritor *descritor = original_descritor;
	LDE_Node* inicio = descritor->inicio;
	LDE_Node* novo = (LDE_Node*)malloc(sizeof(LDE_Node));

	novo->frequencia = 1;
	novo->nodes = node;
	novo->ant = NULL;
	printf("Novo node\n");
	if(inicio == NULL){
		novo->prox = NULL;

		descritor->inicio = novo;
		descritor->fim = novo;
	} else {
		novo->prox = inicio;
		inicio->ant = novo;
		descritor->inicio = novo;
	}
	return novo;
}


// usar a abp pra achar um nodo, e depois mandar para a lista

// não garante que o nodo está na lista
// remove um nodo da lista, atualiza o descritor e retorna o nodo anterior ao removido
LDE_Node *remove_lde_node(lde_descritor *descritor, LDE_Node *nodo){
	LDE_Node *inicio = descritor->inicio;
	LDE_Node *fim = descritor->fim;
	LDE_Node *anterior = NULL;

	printf("Removendo '%s' da lista\n", nodo->info);
	if(descritor->inicio == NULL){
		printf("Lista vazia\n");
		return NULL;
	} else {
		// remove o nodo da lista
		if(nodo == inicio){
			// nodo no início da lista
			printf("Nodo no inicio da lista\n");
			inicio = nodo->prox;
			inicio->ant = NULL;
			anterior = inicio;
		} else
		if(nodo == fim) {
			fim = nodo->ant;
			fim->prox = NULL;
			anterior = nodo->ant;
		} else {
			// nodo no meio da lista
			nodo->ant->prox = nodo->prox;
			if(nodo->prox != NULL)
				nodo->prox->ant = nodo->ant;
			anterior = nodo->ant;
		}
		nodo->prox = NULL;
		nodo->ant = NULL;
	}
	return anterior;
}

// 
// coloca um nodo na lista ordenando por frequencia
void insere_lde_frequencia(lde_descritor *descritor, LDE_Node *inicio, LDE_Node *nodo){
	if(inicio == NULL){
		descritor->inicio = nodo;
		descritor->fim = nodo;
		nodo->prox = NULL;
		nodo->ant = NULL;
	} else {
		LDE_Node *aux = inicio;
		// coloca o nodo após o aux
		while(aux->prox != NULL && nodo->frequencia > aux->prox->frequencia){
			aux = aux->prox;
		}
		printf("Colocando %s[%d] após %s[%d]\n", nodo->info, nodo->frequencia, aux->info, aux->frequencia);

		nodo->ant = aux;
		nodo->prox = aux->prox;
		if(nodo->prox != NULL)
			nodo->prox->ant = nodo;
		aux->prox = nodo;
		if(descritor->fim == aux)
			descritor->fim = nodo;
	}
}

// Funções de impressão
void imprime_lde(LDE_Node *inicio){
	LDE_Node *atual = inicio;
	if(atual != NULL){
		printf("%d %s\n", atual->frequencia, atual->info);
		imprime_lde(atual->prox);
	}
}

void imprime_lde_linha(LDE_Node *inicio){
	LDE_Node *atual = inicio;
	while(atual != NULL){
		printf("%s[%d] -> ", atual->info, atual->frequencia);
		atual = atual->prox;
	}
	printf("\n");
}

void imprime_inverso_lde(LDE_Node *inicio){
	LDE_Node *atual = inicio;
	while(atual != NULL && atual->prox != NULL){
		printf("->%s", atual->info);
		atual = atual->prox;
	}
	//printf("\nretornando do termo '%s'\n", atual->info);
	while(atual != NULL){
		printf("%d %s\n", atual->frequencia, atual->info);
		atual = atual->ant;
	}
}

void imprime_lde_consultas(TipoConsulta *inicio){
	while(inicio != NULL){
		printf("%d - ", inicio->frequencia);
		imprime_lde_linha(inicio->termos);
		inicio=inicio->prox;
	}
}