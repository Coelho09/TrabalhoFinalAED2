#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "repositorio.h"
typedef struct NoAB {
    palavra_busca entrada;
    struct NoAB* esquerda;
    struct NoAB* direita;
} NoAB;

NoAB* inserir_na_ab(NoAB* no, palavra_busca* nova_entrada);
palavra_busca* buscar_na_ab(NoAB* no, char* palavra);
void liberar_ab(NoAB* no);

#endif