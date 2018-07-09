#ifndef AVL_H
#define AVL_H

// Bibliotecas Locais
#include "../headers/LDC.h"

typedef struct st_AVL{
	char *chave;
	LDC *consultas;
	int bf;
	struct st_AVL *left;
	struct st_AVL *rigth;
}AVL;

//------------------------------OPERAÇÕES BÁSICAS-------------------------------
//Função que insere uma Localidade na AVL
AVL* insertAVL(AVL* tree, char *chave, int* isBalanced);

//Função que busca os dados de uma Localidade na AVL
AVL* searchAVL(AVL* tree, char *chave);

//-----------------------------------ROTAÇÕES-----------------------------------
AVL* rotationLeft(AVL* node);
AVL* rotationRight(AVL* node);
AVL* doubleRotationLeft(AVL* node);
AVL* doubleRotationRight(AVL* node);

#endif // AVL_H
