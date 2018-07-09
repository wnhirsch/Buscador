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
