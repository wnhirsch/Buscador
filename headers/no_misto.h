/*
	Um nó que é ao mesmo tempo uma árvore abp e uma lista duplamente encadeada
	abp pra achar o nó mais rapidamente
	e lde pra organizar os termos por frequencia
*/

typedef struct s_no_misto {
	char* info;
	int frequencia = 1;
	s_no_misto* prox, ant;
	s_no_misto* esq, dir;
} no_misto;