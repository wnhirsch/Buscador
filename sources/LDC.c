// Bibliotecas Globais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bibliotecas Locais
#include "../headers/LDC.h"

//------------------------------OPERAÇÕES BÁSICAS-------------------------------
LDC* insertFirstLDC(LDC* list, char chave[], int frequencia, LDC* termos){
    // Cria o novo nodo
    LDC *new_code = (LDC*)malloc(sizeof(LDC));
    new_code->frequencia = frequencia;
    strcpy(new_code->chave, chave);
    new_code->termos = termos;

    // Se a lista for nula simplesmente insere
    if(list == NULL){
        new_code->prev = new_code;
        new_code->next = new_code;
    }
    // Caso contrario insere entre o seu nodo final e o inicial
    else{
        new_code->next = list;
        new_code->prev = list->prev;
        list->prev->next = new_code;
        list->prev = new_code;
    }

    return new_code;
}

LDC* removeLDC(LDC* list, char chave[], LDC* termos){
    LDC *actual;
    int achou = 0;  // flag

    // Se a lista não for nula
    if(list != NULL){
        actual = list;
        // Percorre a lista procurando o TERMO ou a CONSULTA a ser removida
        do{
            if(strcmp(chave, actual->chave) == 0 &&
               compareLDC(actual->termos,termos) == 0)
                achou = 1;
            else
                actual = actual->next;
        }while((actual != list) && !achou);

        // Se achou remove
        if(achou){
            if(list == list->next)
                list = NULL;
            else{
                actual->next->prev = actual->prev;
                actual->prev->next = actual->next;
                if(actual == list)
                    list = actual->next;
                free(actual);
            }
        }
    }

  return list;
}

LDC* copyLDC(LDC* list){
    // Se a lista não for nula
    if(list != NULL){
        LDC *newList = NULL, *aux = list->prev;

        // Insere cada um dos nodos dela em uma nova lista
        do{
            newList = insertFirstLDC(newList, aux->chave, aux->frequencia, aux->termos);
            aux = aux->prev;
        }while(aux != list->next);

        return newList;
    }
    return NULL;
}

LDC* appendLDC(LDC *nodeA, LDC *nodeB){
    // Se as duas listas existem conecta as duas
    if(nodeA != NULL && nodeB != NULL){
        LDC *fimA = nodeA->prev, *fimB = nodeB->prev;

        nodeA->prev = fimB;
        fimB->next = nodeA;

        nodeB->prev = fimA;
        fimA->next = nodeB;

        return nodeA;
    }
    // Caso contrário retorna a que não é nula ou apenas nulo se ambas forem nulo
    else if(nodeA == NULL)
        return nodeB;
    else if(nodeB == NULL)
        return nodeA;
    return NULL;
}

int lengthLDC(LDC* list){
    int length = 0;
    if(list != NULL){
        LDC* aux = list;
        // A cada nodo da lista incrementa o contador e o retorna
        do{
            aux = aux->next;
            length++;
        }while(aux != list);
    }
    return length;
}

int compareLDC(LDC *nodeA, LDC *nodeB){
    // comparando se as duas listas existem
    if(nodeA != NULL && nodeB != NULL){
        LDC *auxA = nodeA, *auxB = nodeB;
        int res_cmp;
        do{
            // comparando cada um dos nodos de cada uma das lista, pra
            // vendo se são iguais
            res_cmp = strcmp(auxA->chave, auxB->chave);
            if(res_cmp != 0)
                return res_cmp;
            auxA = auxA->next;
            auxB = auxB->next;
        }while(nodeA != auxA && nodeB != auxB);

        if(res_cmp == 0){
            if(nodeA == auxA && nodeB == auxB)
                return 0;
            // a primeira lista chegou no início novamente
            else if(nodeA == auxA && nodeB != auxB)
                return -1;
            // a segunda lista chegou no início novamente
            else if(nodeA != auxA && nodeB == auxB)
                return 1;
        }
        else
            return res_cmp;
    }
    else if(nodeA != NULL && nodeB == NULL)
        return 1;
    else if(nodeA == NULL && nodeB != NULL)
        return -1;
    return 0;
}

LDC* sortAlfLDCc(LDC *list){
    LDC *newList = NULL, *actual, *menor;

    // Bubble Sort em ordem decrescente inserindo as menores frequências e as
    // maiores palavras no final
    while(list != NULL){
        menor = list;
        actual = list->next;
        do{
            if(actual->frequencia < menor->frequencia ||
                (actual->frequencia == menor->frequencia &&
                 compareLDC(menor->termos, actual->termos) <= 0))
                    menor = actual;
            actual = actual->next;
        }while(actual != list);

        newList = insertFirstLDC(newList, menor->chave, menor->frequencia, menor->termos);
        list = removeLDC(list, menor->chave, menor->termos);
    }

    return newList;
}

LDC* sortAlfLDCt(LDC *list){
    LDC *newList = NULL, *actual, *menor;

    // Bubble Sort em ordem decrescente inserindo as menores frequências e as
    // maiores palavras no final
    while(list != NULL){
        menor = list;
        actual = list->next;
        do{
            if(actual->frequencia < menor->frequencia ||
                (actual->frequencia == menor->frequencia &&
                 strcmp(menor->chave, actual->chave) <= 0))
                    menor = actual;
            actual = actual->next;
        }while(actual != list);

        newList = insertFirstLDC(newList, menor->chave, menor->frequencia, menor->termos);
        list = removeLDC(list, menor->chave, menor->termos);
    }

    return newList;
}

LDC* removeCopyLDCc(LDC *list){
    if(list != NULL && list != list->next){
        LDC *actual = list, *prox = actual->next, *aux;

        // Para cada consulta da lista compara a sua consulta com a dos outros
        // removendo os iguais e incrementando a sua frequencia
        do{
            do{
                if(compareLDC(actual->termos, prox->termos) == 0){
                    prox->next->prev = prox->prev;
                    prox->prev->next = prox->next;
                    aux = prox->next;
                    free(prox);
                    prox = aux;
                    (actual->frequencia)++;
                    // Exclui o valor repetido e incrementa a frequencia do
                    // primeiro encontrado.
                }
                else
                    prox = prox->next;
            }while(prox != list);
            actual = actual->next;
            prox = actual->next;
            // Garante que toda a lista de listas seja percorrida.
        }while(actual != list->prev);

        return actual;
    }
    return NULL;
}

LDC* removeCopyLDCt(LDC *list){
    if(list != NULL && list != list->next){
        LDC *actual = list, *prox = actual->next, *aux;

        // Para cada termo da lista compara o seu termo com a dos outros
        // removendo os iguais e incrementando a sua frequencia
        do{
            do{
                if(strcmp(actual->chave, prox->chave) == 0){
                    prox->next->prev = prox->prev;
                    prox->prev->next = prox->next;
                    aux = prox->next;
                    free(prox);
                    prox = aux;
                    (actual->frequencia)++;
                    // Exclui o valor repetido e incrementa a frequencia do
                    // primeiro encontrado.
                }
                else
                    prox = prox->next;
            }while(prox != list);
            actual = actual->next;
            prox = actual->next;
            // Garante que toda a lista de listas seja percorrida.
        }while(actual != list->prev);

        return actual;
    }
    return NULL;
}
