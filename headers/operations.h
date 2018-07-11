#ifndef OPERATIONS_H
#define OPERATIONS_H

// Bibliotecas Locais
#include "../headers/LDC.h"
#include "../headers/AVL.h"

void operacaoA (AVL* localidades, FILE* saida, char nome[], int TExpected);

void operacaoB (LDC *consultas, FILE *saida, int TExpected);

void operacaoC (AVL *localidades, FILE *saida, char *local, int TExpected);

void operacaoE (AVL* localidades, FILE* saida, char nome[]);

void operacaoF (LDC *consultas, FILE *saida);

#endif // OPERATIONS_H
