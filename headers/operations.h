#ifndef OPERATIONS_H
#define OPERATIONS_H

// Bibliotecas Locais
#include "../headers/LDC.h"
#include "../headers/AVL.h"

// OPERAÇÃO A. Listar as consultas mais realizadas por localidade. A operação
// recebe como entrada o nome da localidade e um número que indica quantas
// consultas devem ser retornadas como saída. Se o número for zero, todas as
// consultas devem ser listadas. A saída da função é o número que representa a
// quantidade de ocorrências e a respectiva consulta. Restrições: (i) listar um resultado
// por linha; (ii) se a localidade não existir, exibir essa informação; (iii)
// consultas com a mesma frequência devem ser listadas em ordem alfabética.

void operacaoA (AVL* consultasLocais, FILE* saida, char nome[], int TExpected);

// OPERAÇÃO B. Listar as consultas mais realizadas em todo arquivo. A operação
// recebe como entrada um número que indica quantas consultas devem ser retornadas
// como saída. Se o número for zero, todas as consultas devem ser listadas. A
// saída da função é o número que representa a quantidade de ocorrências e a
// respectiva consulta. Restrições: (i) listar um resultado por linha; (ii)
// consultas com a mesma frequência devem ser listadas em ordem alfabética.

void operacaoB (LDC* consultas, FILE* saida, int TExpected);

// OPERAÇÃO C. Listar os termos mais consultados por localidade. A operação recebe
// como entrada o nome da localidade e um número que indica quantos termos devem
// ser retornados como saída. Se o número for zero, todas os termos devem ser
// listados. A saída da função é o número que representa a quantidade de ocorrências
// e o respectivo termo. Restrições: (i) listar um resultado por linha; (ii) se
// a localidade não existir, exibir essa informação; (iii) termos com a mesma
// frequência devem ser listados em ordem alfabética.

void operacaoC (AVL* termosLocais, FILE* saida, char *local, int TExpected);

// OPERAÇÃO D. Listar os termos mais consultados em todo arquivo. A operação
// recebe como entrada um número que indica quantos termos devem ser retornados
// como saída. Se o número for zero, todas os termos devem ser listados. A saída
// da função é o número que representa a quantidade de ocorrências e o respectivo
// termo. Restrições: (i) listar um resultado por linha; (ii) termos com a mesma
// frequência devem ser listados em ordem alfabética.

void operacaoD (AVL* termosLocais, FILE* saida, int TExpected);
// Função recursiva auxiliar para percorrer a árvore
LDC* operacaoDrecursivo(AVL* termosLocais);

// OPERAÇÃO E. Listar tamanho médio das consultas por localidade. A operação recebe
// como entrada o nome da localidade e retorna como saída a média da quantidade
// de termos das consultas na localidade informada. A saída é do tipo int. Truncar
// se o resultado não for inteiro.

void operacaoE (AVL* consultasLocais, FILE* saida, char nome[]);

// OPERAÇÃO F. Listar tamanho médio das consultas em todo arquivo. A operação
// retorna como saída a média da quantidade de termos das consultas do arquivo.
// A saída é do tipo int. Truncar se o resultado não for inteiro.

void operacaoF (LDC* consultas, FILE* saida);

#endif // OPERATIONS_H
