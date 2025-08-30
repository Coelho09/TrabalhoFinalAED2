#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "repositorio.h"

typedef struct NoAVL {
    palavra_busca entrada;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
} NoAVL;

NoAVL* inserir_na_avl(NoAVL* no, palavra_busca* nova_entrada);
palavra_busca* buscar_na_avl(NoAVL* no, char* palavra);
void liberar_avl(NoAVL* no);
palavra_busca* buscar_na_avl_por_frequencia(NoAVL* raiz, int freq);
NoAVL* inserir_na_avl_freq(NoAVL* node, palavra_busca* nova_entrada);

#endif
