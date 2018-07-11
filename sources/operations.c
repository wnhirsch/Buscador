// Bibliotecas Globais
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Bibliotecas Locais
#include "../headers/operations.h"

//---------------------------------OPERAÇÃO A-----------------------------------
void operacaoA (AVL* consultasLocais, FILE* saida, char nome[], int TExpected){
    AVL* localAtual = searchAVL(consultasLocais, nome); // Busca os dados da localidade
    if(localAtual == NULL){ // Se não encontrou informa que a localidade não existe
        fprintf(saida, "Localidade '%s' nao existe na database\n", nome);
        printf("\tLocalidade '%s' inexistente\n", nome);
    }
    else{ // Caso contrário inicia simplificando as consultas
        printf("\tInicia simplificacao das consultas de '%s'\n", nome);
        localAtual->consultas = removeCopyLDCc(localAtual->consultas);
        localAtual->consultas = sortAlfLDCc(localAtual->consultas);
        printf("\tSimplificacao concluida\n");

        // Após isso armazena elas no arquivo
        printf("\tTenta armazenar os dados no arquivo de saida\n");
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
        printf("\tDados armazenados com sucesso!\n");
    }
}

//---------------------------------OPERAÇÃO B-----------------------------------
void operacaoB (LDC *consultas, FILE *saida, int TExpected){
    // Inicia simplificando as consultas
    printf("\tInicia simplificacao de todas as consultas\n");
    consultas = removeCopyLDCc(consultas);
    consultas = sortAlfLDCc(consultas);
    printf("\tSimplificacao concluida\n");

    // Após isso armazena elas no arquivo
    printf("\tTenta armazenar os dados no arquivo de saida\n");
    LDC *actual = consultas;
    do{
        LDC *aux = actual->termos;

        fprintf(saida, "%d ", actual->frequencia);
        fprintf(saida, "%s", aux->chave);

        aux = aux->next;

        while(aux != actual->termos){
            fprintf(saida, ";%s", aux->chave);
            aux = aux->next;
        }
        fprintf(saida, "\n");
        actual = actual->next;
    }while(actual != consultas && --TExpected != 0);

    printf("\tDados armazenados com sucesso!\n");
}

//---------------------------------OPERAÇÃO C-----------------------------------
void operacaoC (AVL *termosLocais, FILE *saida, char nome[], int TExpected){
    AVL *localAtual = searchAVL(termosLocais, nome); // Busca os dados da localidade
    if(localAtual == NULL){ // Se não encontrou informa que a localidade não existe
        fprintf(saida, "Localidade '%s' nao existe na database\n", nome);
        printf("\tLocalidade '%s' inexistente\n", nome);
    }
    else{ // Caso contrário inicia simplificando os termos
        printf("\tInicia simplificacao dos termos de '%s'\n", nome);
        LDC* lista = copyLDC(localAtual->consultas);
        lista = removeCopyLDCt(lista);
        lista = sortAlfLDCt(lista);
        printf("\tSimplificacao concluida\n");

        // Após isso armazena eles no arquivo
        printf("\tTenta armazenar os dados no arquivo de saida\n");
        LDC *aux = lista;
        do{
            fprintf(saida, "%d %s\n", aux->frequencia, aux->chave);
            aux = aux->next;
        }while(aux != lista && --TExpected != 0);
        printf("\tDados armazenados com sucesso!\n");
    }
}

//---------------------------------OPERAÇÃO D-----------------------------------
void operacaoD (AVL *termosLocais, FILE *saida, int TExpected){
    printf("\tInicia simplificacao de todos os termos\n");
    // Busca a lista de termos de todas as localidades na árvore
    LDC* lista = operacaoDrecursivo(termosLocais);
    // Simplifica os termos encontrados
    lista = removeCopyLDCt(lista);
    lista = sortAlfLDCt(lista);
    printf("\tSimplificacao concluida\n");

    // Após isso armazena eles no arquivo
    printf("\tTenta armazenar os dados no arquivo de saida\n");
    LDC *aux = lista;
    do{
        //printf("[%d]%s\n", aux->frequencia, aux->chave);
        fprintf(saida, "%d %s\n", aux->frequencia, aux->chave);
        aux = aux->next;
    }while(aux != lista && --TExpected != 0);
    printf("\tDados armazenados com sucesso!\n");
}

LDC* operacaoDrecursivo(AVL *termosLocais){
    // Se não chegamos no fim da árvore
    if(termosLocais != NULL){
        // criamos uma lista com as consultas dessa localidade
        LDC* lista = copyLDC(termosLocais->consultas);
        // e concatenamos com as localidades seguintes
        lista = appendLDC(lista,operacaoDrecursivo(termosLocais->left));
        lista = appendLDC(lista,operacaoDrecursivo(termosLocais->right));
        return lista;
    }
    return NULL;
}

//---------------------------------OPERAÇÃO E-----------------------------------
void operacaoE (AVL* consultasLocais, FILE* saida, char nome[]){
    AVL* localAtual = searchAVL(consultasLocais, nome); // Busca os dados da localidade
    if(localAtual == NULL){ // Se não encontrou informa que a localidade não existe
        fprintf(saida, "Localidade '%s' nao existe na database\n", nome);
        printf("\tLocalidade '%s' inexistente\n", nome);
    }
    else{ // Caso contrário inicia a contagem
        printf("\tInicia contagem dos termos e consultas de '%s'\n", nome);
        int nconsultas = 0, ntermos = 0, media;
        // Dado a lista de consultas dessa localidade
        LDC *consultas = localAtual->consultas;

        // Para cada consulta
        do{
            // Numero de consultas = sua frequencia
            nconsultas += consultas->frequencia;
            // Numero de termos = tamanho da lista de consultas * sua frequencia
            ntermos += consultas->frequencia * lengthLDC(consultas->termos);
            consultas = consultas->next;
        }while(consultas != localAtual->consultas);

        // Calculamos a média após obter o somatorio dos termos e consultas
        media = ceil((double) ntermos / nconsultas);
        printf("\tCalculos concluidos\n");

        // Após isso armazena a informação no arquivo
        printf("\tTenta armazenar os dados no arquivo de saida\n");
        fprintf(saida, "%d média da quantidade de termos das consultas em '%s'\n", media, nome);
        printf("\tDados armazenados com sucesso!\n");
    }
}

//---------------------------------OPERAÇÃO F-----------------------------------
void operacaoF (LDC *consultas, FILE *saida){
    printf("\tInicia contagem de todos os termos e consultas\n");
    int nconsultas = 0, ntermos = 0, media;
    // Dado a lista de consultas dessa localidade
    LDC* aux = consultas;

    // Para cada consulta
    do{
        // Numero de consultas = sua frequencia
        nconsultas += aux->frequencia;
        // Numero de termos = tamanho da lista de consultas * sua frequencia
        ntermos += aux->frequencia * lengthLDC(aux->termos);
        aux = aux->next;
    }while(aux != consultas);

    // Calculamos a média após obter o somatorio dos termos e consultas
    media = ceil((double) ntermos / nconsultas);
    printf("\tCalculos concluidos\n");

    printf("\tTenta armazenar os dados no arquivo de saida\n");
    // Após isso armazena a informação no arquivo
    fprintf(saida, "%d média da quantidade de termos das consultas do arquivo\n", media);
    printf("\tDados armazenados com sucesso!\n");
}
