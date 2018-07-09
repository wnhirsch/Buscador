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

// Função que imprime a LDC (para debug)
void printLDC(LDC* list);

// Função que ordena uma LDC de Termos por frequencia
LDC* sortFreqLDC(LDC* list);

// Função que ordena uma LDC de Termos por ordem alfabética
LDC* sortAlfLDC(LDC* list);

// Função que procura um termo na lista
LDC* searchLDC(LDC* list, char chave[]);

// Função que compara duas listas e retorna 1 caso sejam iguais
int isEqualLDC(LDC* list1, LDC* list2);

void show_all(LDC* list);

#endif // LDC_H
