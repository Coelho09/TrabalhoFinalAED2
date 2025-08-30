#include "avl-tree.h"
#include <stdlib.h>
#include <string.h>

// Funções de utilidade da AVL (altura, fator de balanceamento, rotações)
int altura( NoAVL *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}


int max(int a, int b)
{
    return (a > b)? a : b;
}



NoAVL* newNode(palavra_busca *nova_entrada)
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
    y->altura = max(altura(y->esquerda),
                    altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda),
                    altura(x->direita)) + 1;

    
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
    x->altura = max(altura(x->esquerda),   
                    altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda),
                    altura(y->direita)) + 1;

    
    return y;
}

int fator_balanceamento(NoAVL* no) {
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

// NoAVL* inserir_na_avl(NoAVL* node, palavra_busca *nova_entrada)
// {
//     NoAVL * insert_node = newNode(nova_entrada);
    
    
//     if (node == NULL)
//         return insert_node;

//     if(strcmp(node->entrada.palavra, insert_node->entrada.palavra) == 0)
//         node->entrada = insert_node->entrada;
//     else if (strcmp(node->entrada.palavra, insert_node->entrada.palavra) >0)
//         node->esquerda  = inserir_na_avl(node->esquerda, &insert_node->entrada);
//     else if (strcmp(node->entrada.palavra, insert_node->entrada.palavra)<0)
//         node->direita = inserir_na_avl(node->direita, &insert_node->entrada);
//     else 
//         return node;

//     // Atualiza a altura do no acestral
//     node->altura = 1 + max(altura(node->esquerda),
//                         altura(node->direita));

//     // verifica o fator de balanceamento do no ancestral!
//     int balance = fator_balanceamento(node);

//     // Casos de desbalanceamento

//     // Esquerda Esquerda   //key < node->left->key
//     if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) < 0)
//         return rotacao_direita(node);

//     // Direita Direita  key > node->right->key
//     if (balance < -1 && strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra) > 0)
//         return rotacao_esquerda(node);

//     // Esquerda Direita key > node->left->key
//     if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) > 0)
//     {
//         node->esquerda =  rotacao_esquerda(node->esquerda);
//         return rotacao_direita(node);
//     }

//     // Direita Esquerda //key < node->right->key
//     if (balance < -1 &&  strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra))
//     {
//         node->direita = rotacao_direita(node->direita);
//         return rotacao_esquerda(node);
//     }

//     //retorna o nó
//     return node;
// }



NoAVL* inserir_na_avl(NoAVL* root, palavra_busca *nova_entrada) {
    NoAVL *insert_node = newNode(nova_entrada);

    
    if (root == NULL)
        return insert_node;

    
    NoAVL *stack[1000]; 
    int top = -1;

    NoAVL *current = root;
    NoAVL *parent = NULL;

    
    while (current != NULL) {
        parent = current;
        stack[++top] = current; // empilha nó visitado

        int cmp = strcmp(insert_node->entrada.palavra, current->entrada.palavra);

        if (cmp == 0) {
            // Palavra já existe → substitui
            if (current->entrada.mData.frequencia > insert_node->entrada.mData.frequencia)
                current->entrada = insert_node->entrada;
            free(insert_node); // não precisa do nó novo
            return root;
        }
        else if (cmp < 0) {
            current = current->esquerda;
        } else {
            current = current->direita;
        }
    }

    // 2. Inserir como filho de "parent"
    if (strcmp(insert_node->entrada.palavra, parent->entrada.palavra) < 0)
        parent->esquerda = insert_node;
    else
        parent->direita = insert_node;

    // 3. Atualizar alturas e balancear de baixo pra cima
    while (top >= 0) {
        NoAVL *node = stack[top--];

        node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
        int balance = fator_balanceamento(node);

        // Caso Esquerda-Esquerda
        if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) < 0) {
            if (top >= 0) {
                NoAVL *parent = stack[top];
                if (parent->esquerda == node)
                    parent->esquerda = rotacao_direita(node);
                else
                    parent->direita = rotacao_direita(node);
            } else {
                root = rotacao_direita(node);
            }
        }
        // Caso Direita-Direita
        else if (balance < -1 && strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra) > 0) {
            if (top >= 0) {
                NoAVL *parent = stack[top];
                if (parent->esquerda == node)
                    parent->esquerda = rotacao_esquerda(node);
                else
                    parent->direita = rotacao_esquerda(node);
            } else {
                root = rotacao_esquerda(node);
            }
        }
        // Caso Esquerda-Direita
        else if (balance > 1 && strcmp(insert_node->entrada.palavra, node->esquerda->entrada.palavra) > 0) {
            node->esquerda = rotacao_esquerda(node->esquerda);
            if (top >= 0) {
                NoAVL *parent = stack[top];
                if (parent->esquerda == node)
                    parent->esquerda = rotacao_direita(node);
                else
                    parent->direita = rotacao_direita(node);
            } else {
                root = rotacao_direita(node);
            }
        }
        // Caso Direita-Esquerda
        else if (balance < -1 && strcmp(insert_node->entrada.palavra, node->direita->entrada.palavra) < 0) {
            node->direita = rotacao_direita(node->direita);
            if (top >= 0) {
                NoAVL *parent = stack[top];
                if (parent->esquerda == node)
                    parent->esquerda = rotacao_esquerda(node);
                else
                    parent->direita = rotacao_esquerda(node);
            } else {
                root = rotacao_esquerda(node);
            }
        }
    }

    return root;
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


void liberar_avl(NoAVL* no) {
    if (no != NULL) {
        liberar_avl(no->esquerda);
        liberar_avl(no->direita);
        free(no);
    }
}


palavra_busca* buscar_na_avl_por_frequencia(NoAVL* raiz, int freq) {
    if (raiz == NULL) return NULL;

    if (freq == raiz->entrada.freqTotal)
        return &raiz->entrada;

    if (freq < raiz->entrada.freqTotal)
        return buscar_na_avl_por_frequencia(raiz->esquerda, freq);
    else
        return buscar_na_avl_por_frequencia(raiz->direita, freq);
}