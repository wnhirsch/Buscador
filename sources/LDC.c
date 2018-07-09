// Bibliotecas Globais
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bibliotecas Locais
#include "../headers/LDC.h"

//------------------------------------------------------------------------------

ldec_node* insertFirstLDC(ldec_node* list, int frequencia, char *chave)
{
    ldec_node *new_code = (ldec_node *)malloc(sizeof(ldec_node));
    new_code->frequencia = frequencia;
    new_code->chave = chave;

    if(list == NULL){
        new_code->ant = new_code;
        new_code->prox = new_code;
    }
    else{
        new_code->prox = list;
        new_code->ant = list->ant;
        list->ant->prox = new_code;
        list->ant = new_code;
    }

    return new_code;
}

ldec_node* removeLDC(ldec_node* list, char *chave)
{
    ldec_node *actual;
    int achou = 0;

    if(list != NULL)
    {
        actual = list;
        do{
            if(strcmp(frequencia, actual->chave) == 0)
                achou = 1;
            else
                actual = actual->prox;
        }while((actual != list) && !achou);

        if(achou){
            if(list == list->prox)
                list = NULL;
            else{
                actual->prox->ant = actual->ant;
                actual->ant->prox = actual->prox;
                if(actual == list)
                    list = actual->prox;
                free(actual);
            }
        }
    }

  return list;
}

void printLDC(ldec_node* list)
{
    ldec_node* aux = list;

    if(list != NULL)
        do{
            printf("\n%s-%d", list->chave, list->frequencia);
            list = list->prox;
        }while(list != aux);
}

ldec_node* sortLDC(ldec_node* list)
{
    ldec_node *newList = NULL, *actual, *menor;

    while(list != NULL){
        menor = list;
        actual = list->prox;
        do{
            if(actual->frequencia < menor->frequencia ||
                (actual->frequencia == menor->frequencia &&
                 strcmp(actual->chave, menor->chave) < 0))
                    menor = actual;
            actual = actual->prox;
        }while(actual != list);

        newList = insertFirstLDC(newList, menor->chave);
        list = removeLDC(list, menor->chave);
    }

    return newList;
}
