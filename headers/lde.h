#define LDE_H "lde.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

// ordenada com inicio < fim
typedef struct s_lde_descritor {
	LDE_Node *inicio, *fim;
} lde_descritor;

// Functions
void imprime_lde(LDE_Node *inicio);
void imprime_inverso_lde(LDE_Node *inicio);
void imprime_lde_linha(LDE_Node *inicio);
void imprime_lde_consultas(TipoConsulta *inicio);

LDE_Node* inicializa_LDE_Node();
//LDE_Node* insere_info_LDE_Node(LDE_Node* inicio, char *info);
LDE_Node* insere_info_LDE_Node_alf(LDE_Node **lista, char *info);
LDE_Node* procura_LDE_Node(LDE_Node* atual, char *info);

// Funções com descritor:
lde_descritor* inicializa_lde_descritor();

// ! Ideia - copiar o conteúdo da string primeiro, e depois enviar pra função
// Ordenar por frequência ( talvez por alfabeticamente dentro ?)
// ordenada com inicio < fim
//LDE_Node *insere_info_lde_inicio(lde_descritor** original_descritor, char *info);
LDE_Node *insere_info_lde_inicio(lde_descritor *original_descritor, char *info);

LDE_Node *insere_termo_lde(lde_descritor* original_descritor, LDE_Node *nodo, char *info);
LDE_Node *remove_lde_node(lde_descritor *descritor, LDE_Node *nodo);
void insere_lde_frequencia(lde_descritor *descritor, LDE_Node *inicio, LDE_Node *nodo);


LDE_Node *insere_consulta_lde(lde_descritor* descritor, LDE_Node *abp_origem_consulta, LDE_Node *consulta);
LDE_Node *insere_consulta_lde_inicio(lde_descritor* original_descritor, LDE_Node *node);