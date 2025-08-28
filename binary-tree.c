#include "arvore_binaria.h"
#include <stdlib.h>
#include <string.h>

NoAB* inserir_na_ab(NoAB* no, EntradaRepositorio nova_entrada) {
    // Implemente a inserção na árvore binária.
    // Lembre-se de atualizar os dados se a palavra já existir[cite: 36, 37].
    // Se a palavra for nova, insira um novo nó.
}

EntradaRepositorio* buscar_na_ab(NoAB* no, const char* palavra) {
    // Implemente a busca na árvore binária.
    // Retorne um ponteiro para a entrada encontrada ou NULL.
}

void liberar_ab(NoAB* no) {
    if (no != NULL) {
        liberar_ab(no->esquerda);
        liberar_ab(no->direita);
        free(no);
    }
}