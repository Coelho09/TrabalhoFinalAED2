#include "binary-tree.h"
#include <stdlib.h>
#include <string.h>

NoAB* newNodeAB(palavra_busca *nova_entrada) {
    NoAB* temp = (NoAB*)malloc(sizeof(NoAB));
    temp->entrada = *nova_entrada;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

NoAB* inserir_na_ab(NoAB* no, palavra_busca *nova_entrada) {
    if (no == NULL) return newNodeAB(nova_entrada);
    int cmp = strcmp(nova_entrada->palavra, no->entrada.palavra);
    if (cmp < 0) no->esquerda = inserir_na_ab(no->esquerda, nova_entrada);
    else if (cmp > 0) no->direita = inserir_na_ab(no->direita, nova_entrada);
    return no;
}

palavra_busca* buscar_na_ab(NoAB* no, char* palavra) {
    NoAB* atual = no;
    while (atual != NULL) {
        int cmp = strcmp(palavra, atual->entrada.palavra);
        if (cmp == 0) return &(atual->entrada);
        else if (cmp < 0) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return NULL;
}

void liberar_ab(NoAB* no) {
    if (no != NULL) {
        liberar_ab(no->esquerda);
        liberar_ab(no->direita);
        free(no);
    }
}
