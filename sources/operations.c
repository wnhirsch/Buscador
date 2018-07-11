// Bibliotecas Globais
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Bibliotecas Locais
#include "../headers/operations.h"

// OPERAÇÃO a. Listar as consultas mais realizadas por localidade. A operação recebe como entrada
// o nome da localidade e um número que indica quantas consultas devem ser retornadas como saída.
// Se o número for zero, todas as consultas devem ser listadas. A saída da função é o número que
// representa a quantidade de ocorrências e a respectiva consulta. Restrições: (i) listar um resultado
// por linha; (ii) se a localidade não existir, exibir essa informação; (iii) consultas com a mesma
// frequência devem ser listadas em ordem alfabética.
void operacaoA (AVL* localidades, FILE* saida, char nome[], int TExpected){
    AVL* localAtual = searchAVL(localidades, nome);
    if(localAtual == NULL){
        fprintf(saida, "Localidade '%s' nao existe na database\n", nome);
        printf("Localidade '%s' inexistente\n", nome);
    }
    else{
        printf("Inicia simplificacao de consultas\n");
        localAtual->consultas = remove_redundancia(localAtual->consultas);
        localAtual->consultas = sortFreqLDC(localAtual->consultas);

        printf("Tenta armazenar as consultas no arquivo de saida\n");
        LDC *actual = localAtual->consultas;
        do{
            fprintf(saida, "%d ", actual->frequencia);
            LDC *aux = actual->termos;

            fprintf(saida, "%s", aux->chave);
            aux = aux->next;

            while(aux != actual->termos){
                fprintf(saida, ";%s", aux->chave);
                aux = aux->next;
            }
            fprintf(saida, "\n");
            actual = actual->next;
        }while(actual != localAtual->consultas && --TExpected != 0);

        printf("Dados armazenados com sucesso!\n\n");

    }
}

// OPERAÇÃO b. Listar as consultas mais realizadas em todo arquivo. A operação recebe como
// entrada um número que indica quantas consultas devem ser retornadas como saída. Se o número
// for zero, todas as consultas devem ser listadas. A saída da função é o número que representa a
// quantidade de ocorrências e a respectiva consulta. Restrições: (i) listar um resultado por linha; (ii)
// consultas com a mesma frequência devem ser listadas em ordem alfabética.
void operacaoB (LDC *consultas, FILE *saida, int TExpected){
    printf("Removendo redundancia\n");
    consultas = remove_redundancia(consultas);
    consultas = sortFreqLDC(consultas);
    consultas = sortSubLDC(consultas);

    printf("Consultas: \n");
    LDC *aux = consultas;
    do {
        printf("[%d]: ", aux->frequencia);
        show_all(aux->termos);
        aux = aux->next;
        printf("\n");
    } while(aux != consultas);

    LDC *actual = consultas;
    printf("Tenta armazenar as consultas no arquivo de saida\n");

    do{
        fprintf(saida, "%d ", actual->frequencia);
        LDC *aux = actual->termos;

        fprintf(saida, "%s", aux->chave);
        aux = aux->next;

        while(aux != actual->termos){
            fprintf(saida, ";%s", aux->chave);
            aux = aux->next;
        }
        fprintf(saida, "\n");
        actual = actual->next;
    }while(actual != consultas && --TExpected != 0);

    printf("Dados armazenados com sucesso!\n\n");
}


// OPERAÇÃO c. Listar os termos mais consultados por localidade. A operação recebe como entrada
// o nome da localidade e um número que indica quantos termos devem ser retornados como saída.
// Se o número for zero, todas os termos devem ser listados. A saída da função é o número que
// representa a quantidade de ocorrências e o respectivo termo. Restrições: (i) listar um resultado por
// linha; (ii) se a localidade não existir, exibir essa informação; (iii) termos com a mesma frequência
// devem ser listados em ordem alfabética.
void operacaoC (AVL *localidades, FILE *saida, char *local, int TExpected){
    AVL *localAtual = searchAVL(localidades, local);
    if(localAtual == NULL){
        fprintf(saida, "Localidade '%s' nao existe na database\n", local);
    } else {
        LDC* lista = localAtual->consultas;

        lista = remove_redundancia_termos(lista);
        lista = sortFreqLDC(lista);
        lista = sortSubTermos(lista);

        LDC *aux = lista;
        printf("Armazenando daods no arquivo de saída\n");
        do {
            //printf("[%d]%s\n", aux->frequencia, aux->chave);
            fprintf(saida, "%d %s\n", aux->frequencia, aux->chave);
            aux = aux->next;
        } while(aux != lista && --TExpected > 0);
    }
}


// OPERAÇÃO d. Listar os termos mais consultados em todo arquivo. A operação recebe como
// entrada um número que indica quantos termos devem ser retornados como saída. Se o número for
// zero, todas os termos devem ser listados. A saída da função é o número que representa a
// quantidade de ocorrências e o respectivo termo. Restrições: (i) listar um resultado por linha; (ii)
// termos com a mesma frequência devem ser listados em ordem alfabética.



// OPERAÇÃO e. Listar tamanho médio das consultas por localidade. A operação recebe como
// entrada o nome da localidade e retorna como saída a média da quantidade de termos das consultas
// na localidade informada. A saída é do tipo int. Truncar se o resultado não for inteiro.

void operacaoE (AVL* localidades, FILE* saida, char nome[]){
    AVL* localAtual = searchAVL(localidades, nome);
    if(localAtual == NULL){
        fprintf(saida, "Localidade '%s' nao existe na database\n", nome);
        printf("Localidade '%s' inexistente\n", nome);
    }
    else{
        printf("Inicia contagem de termos e consultas\n");
        int nconsultas = 0, ntermos = 0, media;
        LDC *consultas = localAtual->consultas;
        do{
            nconsultas += consultas->frequencia;
            ntermos += consultas->frequencia * lengthLDC(consultas->termos);
            consultas = consultas->next;
        }while(consultas != localAtual->consultas);
        media = ceil((double) ntermos / nconsultas);
        fprintf(saida, "%d média da quantidade de termos das consultas em '%s'\n", media, nome);
        printf("Dados armazenados com sucesso!\n\n");
    }
}


// OPERAÇÃO f. Listar tamanho médio das consultas em todo arquivo. A operação retorna como
// saída a média da quantidade de termos das consultas do arquivo. A saída é do tipo int. Truncar se o
// resultado não for inteiro.

void operacaoF (LDC *consultas, FILE *saida)
{
    printf("Inicia contagem de termos e consultas\n");
    int nconsultas = 0, ntermos = 0, media;
    LDC* aux = consultas;
    do{
        nconsultas += aux->frequencia;
        ntermos += aux->frequencia * lengthLDC(aux->termos);
        aux = aux->next;
    }while(aux != consultas);
    media = ceil((double) ntermos / nconsultas);
    fprintf(saida, "%d média da quantidade de termos das consultas do arquivo\n", media);
    printf("Dados armazenados com sucesso!\n\n");
}
