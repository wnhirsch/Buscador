#ifndef LDC_H
#define LDC_H

// Constantes
#define BUFFER_SIZE 512

//------------------- Lista Duplamente Encadeada Circular ----------------------
// LDC que pode tanto representar uma Lista de Consultas de uma localidade como
// uma Lista de Termos de uma Consulta. As váriaveis a seguir são usadas para:
typedef struct st_LDC{
	char chave[BUFFER_SIZE]; // TERMO - string com o Termo
	int frequencia;			 // TERMO/CONSULTA - frequência do Termo/Consulta
	struct st_LDC *termos;   // CONSULTA - Lista de Consultas
	struct st_LDC *next;
	struct st_LDC *prev;
}LDC;

//------------------------------OPERAÇÕES BÁSICAS-------------------------------
// Função que insere um Termo ou Consulta no inicio da LDC
LDC* insertFirstLDC(LDC* list, char chave[], int frequencia, LDC* termos);

// Função que procura um Termo na LDC e o remove
LDC* removeLDC(LDC* list, char chave[], LDC* termos);

// Função que gera uma nova copia da Lista dada como parametro
LDC* copyLDC(LDC* list);

// Função que insere a segunda Lista no fim da primeira
LDC* appendLDC(LDC *nodeA, LDC *nodeB);

// Retorna o tamanho da lista
int lengthLDC(LDC* list);

// Compara a primeira lista circular com a segunda:
// Se forem iguais, retorna 0
// Se a primeira for menor, retorna -1
// Se a primeira for maior, retorna +1
int compareLDC(LDC *nodeA, LDC *nodeB);

// Função que ordena uma lista de CONSULTAS em ordem alfabética e de frequência
LDC* sortAlfLDCc(LDC *list);

// Função que ordena uma lista de TERMOS em ordem alfabética e de frequência
LDC* sortAlfLDCt(LDC *list);

// Função que remove CONSULTAS duplicados na lista de CONSULTAS
LDC* removeCopyLDCc(LDC *list);

// Função que remove TERMOS duplicados na lista de TERMOS
LDC* removeCopyLDCt(LDC *list);

#endif // LDC_H
