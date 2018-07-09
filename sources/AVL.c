// Bibliotecas Globais
#include <stdlib.h>
#include <string.h>

// Bibliotecas Locais
#include "../headers/AVL.h"

//------------------------------OPERAÇÕES BÁSICAS-------------------------------
AVL* insertAVL(AVL* tree, char *chave, int* isBalanced){
    // Se a árvore for Nula inserimos o dado
    if(tree == NULL){
        // Alocamos o nodo
        tree = (AVL*) malloc(sizeof(AVL));
        tree->right = NULL;
        tree->left = NULL;
        strcpy(tree->chave, chave);
        // Definimos o fator de balanceamento como 0 e desligamos a nossa flag
        // que está ligada quando a árvore está balanceada
        tree->bf = 0;
        *isBalanced = 0;
    }
    // Caso contrário verificamos se devemos inserir para a direta
    else if(strcmp(chave, tree->chave) > 0){
        // Chamamos a função recursivamente até inserirmos o nodo
        tree->right = insertAVL(tree->right, chave, isBalanced);
        // Se não tivermos certeza do balanceamento da árvore testamos o fator
        // de balanceamento antigo do nodo atual
        if(!(*isBalanced)){
            switch(tree->bf){
                // Se o fator era -1 devemos realizar rotação nos nodos
                case -1:
                    // Se o filho direito for negativo realizamos RSE
                    if(tree->right->bf == -1)
                        tree = rotationLeft(tree);
                    // Caso contrário RDE
                    else
                        tree = doubleRotationLeft(tree);
                // Se o fator era 1 ela está balanceada
                case 1:
                    tree->bf = 0;
                    *isBalanced = 1;
                    break;
                // Se o fator era 0 ela está balanceada até aqui, mas há
                // possibilidade de rotação, então mantemos a flag como está
                case 0:
                    tree->bf = -1;
                    break;
            }
        }
    }
    else if(strcmp(chave, tree->chave) < 0){
        // Caso contrário inserimos para a esquerda
        tree->left = insertAVL(tree->left, chave, isBalanced);
        // Se não tivermos certeza do balanceamento da árvore testamos o fator
        // de balanceamento antigo do nodo atual
        if(!(*isBalanced)){
            switch(tree->bf){
                // Se o fator era 1 devemos realizar rotação nos nodos
                case 1:
                    // Se o filho esquerdo for negativo realizamos RSD
                    if(tree->left->bf == 1)
                        tree = rotationRight(tree);
                    // Caso contrário RDD
                    else
                        tree = doubleRotationRight(tree);
                // Se o fator era -1 ela está balanceada
                case -1:
                    tree->bf = 0;
                    *isBalanced = 1;
                    break;
                // Se o fator era 0 ela está balanceada até aqui, mas há
                // possibilidade de rotação, então mantemos a flag como está
                case 0:
                    tree->bf = 1;
                    break;
            }
        }
    }
    return tree;
}

AVL* searchAVL(AVL* tree, char *chave){
    // Se a árvore está vazia não retornamos nenhum código ('\0')
    if (tree == NULL)
        return NULL;
    // Caso encontremos o caractere Alfanumérico, retornamos seu igual em Morse
    else if(strcmp(chave, tree->chave) == 0)
        return tree;
    // Caso o caractere buscado for menor procuramos a esquerda
    else if(strcmp(chave, tree->chave) < 0)
        return searchAVL(tree->left, chave);
    // Caso contrário a direita
    else
        return searchAVL(tree->right, chave);
}

//-----------------------------------ROTAÇÕES-----------------------------------
AVL* rotationLeft(AVL* node){
    AVL *nodeSon = node->right;
    node->right = nodeSon->left;
    nodeSon->left = node;
    node->bf = 0;
    node = nodeSon;
    return node;
}

AVL* rotationRight(AVL* node){
    AVL *nodeSon = node->left;
    node->left = nodeSon->right;
    nodeSon->right = node;
    node->bf = 0;
    node = nodeSon;
    return node;
}

AVL* doubleRotationLeft(AVL* node){
    node->right = rotationRight(node->right);
    node = rotationLeft(node);
    return node;
}

AVL* doubleRotationRight(AVL* node){
    node->left = rotationLeft(node->left);
    node = rotationRight(node);
    return node;
}
