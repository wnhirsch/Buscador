#define STRUCT_H "structs.h"

// Structs
typedef struct lde_node {
	char *info;
	int frequencia;
	struct lde_node *prox, *ant;
	struct lde_node *nodes;
} LDE_Node;

// lista de listas ( consultas )
typedef struct s_lde_lde {
	int frequencia;
	struct s_lde_lde *prox, *ant;
	LDE_Node *termos; // lista de termos da consulta
} TipoConsulta;