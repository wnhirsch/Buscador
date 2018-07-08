#define LDEC_H

// Lista Duplamente Encadeada Circular

typedef struct s_ldec_node {
	char *chave;
	int frequencia;
	struct s_ldec_node *prox, *ant;
	struct s_ldec_node *info;
} ldec_node;

// Caracteristica :
// Aponta sempre para o primeiro termo
// O ultimo termo aponta para o primeiro
// e o primeiro termo aponta para o ultimo

// Insere uma consulta em uma lista de consultas de uma localidade
// ordena por ordem de frequência ascendente
// criando ldec de consultas da localidade
ldec_node *insere_consulta_no_local(ldec_node **consulta, ldec_node *termos);

// insere uma consulta em uma lista de consultas de todo o arquivo
// ordena por ordem de frequência ascendente
ldec_node *insere_consulta_no_universo(ldec_node **inicio, ldec_node *termos);

// a mesma coisa que as de cima, mas é uma lista qualquer dada
ldec_node *insere_consulta_na_lista(ldec_node **lista, ldec_node *termos);

// insere no início da lista dada.
// e retorna o novo início
ldec_node *insere_no_inicio(ldec_node *inicio);

// Insere termo em uma lista
// ordena por frequencia
ldec_node *ldec_insere_termo(ldec_node *inicio, char *termo);

// ordena alfabeticamente
ldec_node *ldec_insere_termo_alf(ldec_node **inicio, char *termo);

// compara duas listas circulares, se forem iguais, retorna 0,
// se a primeira for menor, retorna -1,
// se a primeira for maior, retorna 1
int ldec_cmp(ldec_node *nodeA, ldec_node *nodeB);

// void ldec_imprime(ldec_node *inicio);
// ldec_node* insertFirstLDC(ldec_node* list, int frequencia, char *chave);
// ldec_node* removeLDC(ldec_node* list, char *chave);
// void printLDC(ldec_node* list);
// ldec_node* sortLDC(ldec_node* list);
