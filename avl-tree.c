#include "avl-tree.h"
#include <stdlib.h>
#include <string.h>

// Funções de utilidade da AVL (altura, fator de balanceamento, rotações)
int height( NoAVL *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}



NoAVL* newNodeAVL(palavra_busca *nova_entrada)
{
    NoAVL* node = (NoAVL*)
                        malloc(sizeof(NoAVL));
    node->entrada  = *nova_entrada;
    node->esquerda   = NULL;
    node->direita  = NULL;
    node->altura = 1;  // novo no passa a ser folha
    return(node);
}



NoAVL *rotacao_direita(NoAVL *y)
{
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    // rotacao
    x->direita = y;
    y->esquerda = T2;

    // atualiza as alturas
    y->altura = max(height(y->esquerda),
                    height(y->direita)) + 1;
    x->altura = max(height(x->esquerda),
                    height(x->direita)) + 1;

    
    return x;
}
// Implemente as rotações

NoAVL* rotacao_esquerda(NoAVL* x){
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    // rotacao
    y->esquerda = x;
    x->direita = T2;

    // atualiza as alturas
    x->altura = max(height(x->esquerda),   
                    height(x->direita)) + 1;
    y->altura = max(height(y->esquerda),
                    height(y->direita)) + 1;

    
    return y;
}

int fator_balanceamento(NoAVL* no) {
    return no ? height(no->esquerda) - height(no->direita) : 0;
}

NoAVL* inserir_na_avl(NoAVL* node, palavra_busca *nova_entrada)
{
    NoAVL * insert_node = newNodeAVL(nova_entrada);
    
    
    if (node == NULL)
        return insert_node;

    if(strcmp(node->entrada.palavra, insert_node->entrada.palavra) == 0)
        if(node->entrada.mData.frequencia < insert_node->entrada.mData.frequencia)
        {
            node->entrada = insert_node->entrada;
        }
    else if (strcmp(node->entrada.palavra, insert_node->entrada.palavra) >0)
        node->esquerda  = inserir_na_avl(node->esquerda, &insert_node->entrada);
    else if (strcmp(node->entrada.palavra, insert_node->entrada.palavra)<0)
        node->direita = inserir_na_avl(node->direita, &insert_node->entrada);
    else 
        return node;

    // Atualiza a altura do no acestral
    node->altura = 1 + max(height(node->esquerda),
                        height(node->direita));

    // verifica o fator de balanceamento do no ancestral!
    int balance = fator_balanceamento(node);

    // Casos de desbalanceamento

    // Esquerda Esquerda   //key < node->left->key
    if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) < 0)
        return rotacao_direita(node);

    // Direita Direita  key > node->right->key
    if (balance < -1 && strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra) > 0)
        return rotacao_esquerda(node);

    // Esquerda Direita key > node->left->key
    if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) > 0)
    {
        node->esquerda =  rotacao_esquerda(node->esquerda);
        return rotacao_direita(node);
    }

    // Direita Esquerda //key < node->right->key
    if (balance < -1 &&  strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra))
    {
        node->direita = rotacao_direita(node->direita);
        return rotacao_esquerda(node);
    }

    //retorna o nó
    return node;
}


NoAVL* inserir_na_avl_freq(NoAVL* node, palavra_busca *nova_entrada)
{
    NoAVL * insert_node = newNodeAVL(nova_entrada);
    
    
    if (node == NULL)
        return insert_node;

    if(node->entrada.freqTotal == insert_node->entrada.freqTotal)
        if(node->entrada.mData.frequencia < insert_node->entrada.mData.frequencia)
        {
            node->entrada = insert_node->entrada;
        }
    else if (node->entrada.freqTotal > insert_node->entrada.freqTotal)
        node->esquerda  = inserir_na_avl_freq(node->esquerda, &insert_node->entrada);
    else if (node->entrada.freqTotal < insert_node->entrada.freqTotal)
        node->direita = inserir_na_avl_freq(node->direita, &insert_node->entrada);
    else 
        return node;

    // Atualiza a altura do no acestral
    node->altura = 1 + max(height(node->esquerda),
                        height(node->direita));

    // verifica o fator de balanceamento do no ancestral!
    int balance = fator_balanceamento(node);

    // Casos de desbalanceamento

    // Esquerda Esquerda   //key < node->left->key
    if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) < 0)
        return rotacao_direita(node);

    // Direita Direita  key > node->right->key
    if (balance < -1 && strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra) > 0)
        return rotacao_esquerda(node);

    // Esquerda Direita key > node->left->key
    if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) > 0)
    {
        node->esquerda =  rotacao_esquerda(node->esquerda);
        return rotacao_direita(node);
    }

    // Direita Esquerda //key < node->right->key
    if (balance < -1 &&  strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra))
    {
        node->direita = rotacao_direita(node->direita);
        return rotacao_esquerda(node);
    }

    //retorna o nó
    return node;
}

// A busca na arvore AVL é feita da mesma forma que a busca na arvore BST
// palavra_busca* buscar_na_avl(NoAVL* no,char* palavra) {
    
//     if (no == NULL || strcmp(no->entrada.palavra, palavra ) == 0)
//         return no;

    
//     if (strcmp(no->entrada.palavra,palavra) < 0)
//         return buscar_na_ab(no->direita, palavra);

    
//     return buscar_na_ab(no->esquerda, palavra);
// }


palavra_busca* buscar_na_avl(NoAVL* no, char* palavra) {
    

    
      NoAVL* curr = no;
    
    while (curr != NULL) {
        
        
        if (strcmp(curr->entrada.palavra, palavra) == 0)
            return &(curr->entrada);
            
         //curr->data < x
        else if (strcmp(curr->entrada.palavra, palavra) < 0) 
            curr = curr->direita;
            
        // Search in left subtree
        else
            curr = curr->esquerda;
    }
    
    
    return NULL;
}


palavra_busca* buscar_na_avl_por_frequencia(NoAVL* no, int freq) {
    

    
      NoAVL* curr = no;
    
    while (curr != NULL) {
        
        
        if (curr->entrada.freqTotal ==  freq)
            return &(curr->entrada);
            
         //curr->data < x
        else if (curr->entrada.freqTotal < freq) 
            curr = curr->direita;
            
        // Search in left subtree
        else
            curr = curr->esquerda;
    }
    
    
    return NULL;
}



void liberar_avl(NoAVL* no) {
    if (no != NULL) {
        liberar_avl(no->esquerda);
        liberar_avl(no->direita);
        free(no);
    }
}