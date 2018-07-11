// Bibliotecas Globais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bibliotecas Locais
#include "../headers/LDC.h"

//------------------------------OPERAÇÕES BÁSICAS-------------------------------
LDC* insertFirstLDC(LDC* list, char chave[], int frequencia, LDC* termos){
    LDC *new_code = (LDC*)malloc(sizeof(LDC));
    new_code->frequencia = frequencia;
    strcpy(new_code->chave, chave);
    new_code->termos = termos;

    if(list == NULL){
        new_code->prev = new_code;
        new_code->next = new_code;
    }
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
    int achou = 0;

    if(list != NULL)
    {
        actual = list;
        do{
            if(strcmp(chave, actual->chave) == 0 &&
               isEqualLDC(actual->termos,termos))
                achou = 1;
            else
                actual = actual->next;
        }while((actual != list) && !achou);

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

void printLDC(LDC* list){
    LDC* aux = list;

    if(list != NULL)
        do{
            printf("\n%s-%d", list->chave, list->frequencia);
            list = list->next;
        }while(list != aux);
}

LDC* sortFreqLDC(LDC* list){
    LDC *newList = NULL, *actual, *menor;

    while(list != NULL){
        menor = list;
        actual = list->next;
        do{
            if(actual->frequencia < menor->frequencia ||
                (actual->frequencia == menor->frequencia &&
                 strcmp(actual->chave, menor->chave) > 0))
                    menor = actual;
            actual = actual->next;
        }while(actual != list);

        newList = insertFirstLDC(newList, menor->chave, menor->frequencia, menor->termos);
        list = removeLDC(list, menor->chave, menor->termos);
    }

    return newList;
}

LDC* sortAlfLDC(LDC* list){
    LDC *newList = NULL, *actual, *maior;

    while(list != NULL){
        maior = list;
        actual = list->next;
        do{
            if(strcmp(actual->chave, maior->chave) > 0)
                    maior = actual;
            actual = actual->next;
        }while(actual != list);

        newList = insertFirstLDC(newList, maior->chave, maior->frequencia, maior->termos);
        list = removeLDC(list, maior->chave, maior->termos);
    }

    return newList;
}

LDC* sortSubLDC(LDC *list){
    printf("Sorting\n");

    LDC *atual = list, *prox;
    while(atual->next != list){
        prox = atual->next;

        if(atual->frequencia == prox->frequencia){
            int res_cmp = ldc_cmp(atual->termos, prox->termos);
            if(res_cmp >= 1){
                printf("Trocando:\n");
                atual->next = prox->next;
                prox->prev = atual->prev;

                atual->prev->next = prox;
                prox->next->prev = atual;

                atual->prev = prox;
                prox->next = atual;

                atual = prox;
            }
        }
        atual = atual->next;
    };

    printf("End sort\n");
    return list;
}


LDC *sortSubTermos(LDC *inicio){
    LDC *aux = inicio;

    while( aux->next != inicio){
        LDC *prox = aux->next;

        if (aux->frequencia == aux->next->frequencia
        && strcmp(aux->chave, aux->next->chave) >= 1){

            aux->next = prox->next;
            prox->prev = aux->prev;

            aux->prev->next = prox;
            prox->next->prev = aux;

            aux->prev = prox;
            prox->next = aux;

            aux = prox;
        }
        aux = aux->next;
    }

    while(inicio->prev->frequencia > inicio->frequencia){
        inicio = inicio->prev;
    }
    while(inicio->prev->frequencia == inicio->frequencia && strcmp(inicio->prev->chave, inicio->chave) >= 1){
        inicio = inicio->prev;
    }
    return inicio;
}


// Compara a primeira lista circular com a segunda:
// Se forem iguais, retorna 0
// Se a primeira for menor, retorna -1
// Se a primeira for maior, retorna +1
int ldc_cmp(LDC *nodeA, LDC *nodeB){
    LDC *auxA = nodeA, *auxB = nodeB;
    // comparando se as duas listas existem
    if(auxA != NULL && auxB == NULL){
        return 1;
    } else
    if(auxA == NULL && auxB != NULL){
        return -1;
    } else {
        int res_cmp;

        do {
            // comparando cada um dos nodos de cada uma das lista, pra
            // vendo se são iguais
            res_cmp = strcmp(auxA->chave, auxB->chave);
            if(res_cmp != 0){
                return res_cmp;
            }
            auxA = auxA->next;
            auxB = auxB->next;
        } while(nodeA != auxA && nodeB != auxB);

        if(res_cmp == 0 && nodeA == auxA && nodeB == auxB){
            // as duas listas são exatamente iguais
            return 0;
        } else
        if(nodeA == auxA){
            // a primeira lista chegou no início novamente
            return -1;
        } else
        if(nodeB == auxB){
            // a segunda lista chegou no início novamente
            return 1;
        } else {
            // as duas listas tem o mesmo tamanho
            // retorna a última comparação
            return res_cmp;
        }
    }
}


LDC* remove_redundancia(LDC *list){
    LDC *actual = list, *prox = actual->next, *aux;

    printf("Inicia simplificacao de consultas\n");

    if(actual != prox){
        do{
            do{
                if(isEqualLDC(actual->termos, prox->termos)){
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
            }while(prox != actual);
            actual = actual->next;
            prox = actual->next;
            // Garante que toda a lista de listas seja percorrida.
        }while(actual != list->prev);
    }
    return actual;
}


LDC* remove_redundancia_termos(LDC *inicio){
    LDC *atual = inicio, *prox=atual->next, *prev = atual->prev;

    if (atual == atual->next){
        return atual;
    }

    do {
        LDC *aux = atual->next;
        while(aux != inicio){
            if(strcmp(atual->chave, aux->chave) == 0){
                (atual->frequencia)++;

                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;

                prev = aux->prev;
                free(aux);
                aux = prev;
            }
            aux = aux->next;
        }
        atual = atual->next;
    } while(atual != inicio);

    return atual;
}

LDC* searchLDC(LDC* list, char chave[]){
    LDC *actual;
    int achou = 0;

    if(list != NULL)
    {
        actual = list;
        do{
            if(strcmp(chave, actual->chave) == 0)
                achou = 1;
            else
                actual = actual->next;
        }while((actual != list) && !achou);

        if(achou)
            return actual;
        else
            return NULL;
    }

  return list;
}

int isEqualLDC(LDC* list1, LDC* list2){
    if(list1 == NULL && list2 == NULL)
        return 1;

    else if((list1 != NULL) != (list2 != NULL))
        return 0;

    else{
        LDC *aux1 = list1, *aux2 = list2;


        do{
            if(strcmp(aux1->chave, aux2->chave) != 0)
                return 0;
            aux1 = aux1->next;
            aux2 = aux2->next;
        }while(list1 != aux1 && list2 != aux2);

        if(list1 == aux1 && list2 == aux2)
            return 1;
        else
            return 0;
    }
}


void show_all(LDC* list)
{
    LDC* aux = list;
    do{
        printf("%s;", aux->chave);
        aux = aux->next;
    }while(aux != list);
}

int lengthLDC(LDC* list)
{
    int length = 0;
    if(list != NULL){
        LDC* aux = list;
        do{
            aux = aux->next;
            length++;
        }while(aux != list);
    }
    return length;
}
