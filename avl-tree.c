#include "avl-tree.h"
#include <stdlib.h>
#include <string.h>

int height(NoAVL *N) {
    if (N == NULL) return 0;
    return N->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL* newNodeAVL(palavra_busca *nova_entrada) {
    NoAVL* node = (NoAVL*) malloc(sizeof(NoAVL));
    node->entrada  = *nova_entrada;
    node->esquerda   = NULL;
    node->direita  = NULL;
    node->altura = 1;
    return(node);
}

NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(height(y->esquerda), height(y->direita)) + 1;
    x->altura = max(height(x->esquerda), height(x->direita)) + 1;
    return x;
}

NoAVL* rotacao_esquerda(NoAVL* x) {
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(height(x->esquerda), height(x->direita)) + 1;
    y->altura = max(height(y->esquerda), height(y->direita)) + 1;
    return y;
}

int fator_balanceamento(NoAVL* no) {
    if (no == NULL) return 0;
    return height(no->esquerda) - height(no->direita);
}

NoAVL* inserir_na_avl(NoAVL* node, palavra_busca *nova_entrada) {
    if (node == NULL) return newNodeAVL(nova_entrada);
    int cmp = strcmp(nova_entrada->palavra, node->entrada.palavra);
    if (cmp < 0) node->esquerda  = inserir_na_avl(node->esquerda, nova_entrada);
    else if (cmp > 0) node->direita = inserir_na_avl(node->direita, nova_entrada);
    else return node;

    node->altura = 1 + max(height(node->esquerda), height(node->direita));
    int balance = fator_balanceamento(node);

    if (balance > 1 && strcmp(nova_entrada->palavra, node->esquerda->entrada.palavra) < 0) return rotacao_direita(node);
    if (balance < -1 && strcmp(nova_entrada->palavra, node->direita->entrada.palavra) > 0) return rotacao_esquerda(node);
    if (balance > 1 && strcmp(nova_entrada->palavra, node->esquerda->entrada.palavra) > 0) {
        node->esquerda =  rotacao_esquerda(node->esquerda);
        return rotacao_direita(node);
    }
    if (balance < -1 && strcmp(nova_entrada->palavra, node->direita->entrada.palavra) < 0) {
        node->direita = rotacao_direita(node->direita);
        return rotacao_esquerda(node);
    }
    return node;
}

NoAVL* inserir_na_avl_freq(NoAVL* node, palavra_busca *nova_entrada) {
    if (node == NULL) return newNodeAVL(nova_entrada);
    if (nova_entrada->freqTotal < node->entrada.freqTotal) node->esquerda  = inserir_na_avl_freq(node->esquerda, nova_entrada);
    else if (nova_entrada->freqTotal > node->entrada.freqTotal) node->direita = inserir_na_avl_freq(node->direita, nova_entrada); // >= para inserir duplicados
    else return node;

    node->altura = 1 + max(height(node->esquerda), height(node->direita));
    int balance = fator_balanceamento(node);

    if (balance > 1 && nova_entrada->freqTotal < node->esquerda->entrada.freqTotal) return rotacao_direita(node);
    if (balance < -1 && nova_entrada->freqTotal >= node->direita->entrada.freqTotal) return rotacao_esquerda(node);
    if (balance > 1 && nova_entrada->freqTotal >= node->esquerda->entrada.freqTotal) {
        node->esquerda = rotacao_esquerda(node->esquerda);
        return rotacao_direita(node);
    }
    if (balance < -1 && nova_entrada->freqTotal < node->direita->entrada.freqTotal) {
        node->direita = rotacao_direita(node->direita);
        return rotacao_esquerda(node);
    }
    return node;
}

palavra_busca* buscar_na_avl(NoAVL* no, char* palavra) {
    NoAVL* atual = no;
    while (atual != NULL) {
        int cmp = strcmp(palavra, atual->entrada.palavra);
        if (cmp == 0) return &(atual->entrada);
        else if (cmp < 0) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return NULL;
}

palavra_busca* buscar_na_avl_por_frequencia(NoAVL* no, int freq) {
    NoAVL* atual = no;
    while (atual != NULL) {
        if (freq == atual->entrada.freqTotal) return &(atual->entrada);
        else if (freq < atual->entrada.freqTotal) atual = atual->esquerda;
        else atual = atual->direita;
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
