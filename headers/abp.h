#define ABP_H "abp.h"

#ifndef LDE_H
#include "lde.h"
#endif

#ifndef LDEC_H
#include "lde_circular.h"
#endif

typedef struct s_abp_node{
	char *chave;
	int frequencia;
	LDE_Node *node; // lista de termos
	TipoConsulta *consultas; // arvore de consultas
	LDE_Node *lde_cidade; // ponteiro para a lista de cidades organizada por frequencia
	struct s_abp_node *esq, *dir;
	ldec_node *info; // link para o nodo correpondente na lista de consultas
} abp_node;

// imprime as chaves da abp
void imprime_abp(abp_node *inicio, int height);
// imprime os nodes da abp em linha
void imprime_abp_consulta(abp_node *inicio, int height);


abp_node *abp_procurar_chave(abp_node *raiz, char *info);

// Insere uma string (info) na abp e retorna o nodo inserido
// atualiza a raiz
abp_node *abp_inserir_node(abp_node **inicio, char *info);



// procura uma consulta na abp. se não encontrar, cria um nodo com aquela consulta
// retorna sempre a raiz da árvore ou sub-árvore
abp_node *abp_insere_consulta(abp_node *raiz, LDE_Node *termos);

// retorna o nodo adicionado ou modificado
abp_node *abp_insere_consulta2(abp_node **inicio, LDE_Node *termos);