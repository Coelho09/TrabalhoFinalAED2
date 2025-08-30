#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_search.h"

void inicializa_vetor(RepositorioVetor* rv){
    rv->tamanho = 0;
    rv->capacidade = 128;
    rv->vetor = (palavra_busca *) malloc (rv->capacidade * sizeof(palavra_busca));
}

void inserir_no_vetor(RepositorioVetor *rv, palavra_busca * nova_palavra){
    if (rv->tamanho >= rv->capacidade) {
        rv->capacidade *= 2;
        rv->vetor = (palavra_busca *) realloc(rv->vetor, rv->capacidade * sizeof(palavra_busca));
        if (rv->vetor == NULL) {
            perror("Falha ao realocar memoria para o vetor");
            exit(1);
        }
    }
    rv->vetor[rv->tamanho] = *nova_palavra;
    rv->tamanho++;
}

void shell_sort_vetor(RepositorioVetor  *rv, int vec_size){
    int i, j, h = 1;
    palavra_busca aux;
    if (vec_size <= 1) return;
    do { h = h * 3 + 1; } while (h < vec_size);
    do {
        h /= 3;
        for (i = h; i < vec_size; i++) {
            aux = rv->vetor[i];
            j = i;
            while (j >= h && strcmp(rv->vetor[j - h].palavra, aux.palavra) > 0) {
                rv->vetor[j] = rv->vetor[j - h];
                j -= h;
            }
            rv->vetor[j] = aux;
        }
    } while (h != 1);
}

palavra_busca* buscar_no_vetor(RepositorioVetor* rv, char* palavra) {
    int low = 0;
    int high = rv->tamanho - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(rv->vetor[mid].palavra, palavra);
        if (cmp == 0) return &rv->vetor[mid];
        if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return NULL;
}

void liberar_vetor(RepositorioVetor* rv) {
    if (rv->vetor != NULL) {
        free(rv->vetor);
    }
    rv->vetor = NULL;
    rv->tamanho = 0;
    rv->capacidade = 0;
}
