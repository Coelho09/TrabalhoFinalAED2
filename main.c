#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "repositorio.h"
#include "binary_search.h"
#include "binary-tree.h"
#include "avl-tree.h"
#include "utils.h"
#include "processa_arquivos.h" // onde está processar_arquivo

// Funções para a interação com o usuário
void menu_principal();
void carregar_arquivos();
void buscar_palavra();
void buscar_por_frequencia();

// Estruturas globais
RepositorioVetor repo_vetor;
NoAB* raiz_ab = NULL;
NoAVL* raiz_avl = NULL;
NoAVL* raiz_avl_frequencia = NULL;

int main() {
    inicializa_vetor(&repo_vetor);

    int opcao;
    do {
        menu_principal();
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                carregar_arquivos();
                break;
            case 2:
                buscar_palavra();
                break;
            case 3:
                buscar_por_frequencia();
                break;
            case 0:
                printf("Fim!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberar_vetor(&repo_vetor);
    liberar_ab(raiz_ab);
    liberar_avl(raiz_avl);
    liberar_avl(raiz_avl_frequencia);

    return 0;
}

void menu_principal() {
    printf("\n### Repositorio de Letras de Musicas ###\n");
    printf("1. Carregar arquivos de texto\n");
    printf("2. Buscar por palavra\n");
    printf("3. Buscar por frequencia\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void carregar_arquivos() {
    char nome_arquivo[256];
    printf("Digite o nome do arquivo de musica (.txt): ");
    scanf("%s", nome_arquivo);

    int tamanho = 0;

    clock_t inicio = clock();
    palavra_busca* lista = processa_arquivo(nome_arquivo, &tamanho);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (lista == NULL) {
        printf("Erro ao processar o arquivo!\n");
        return;
    }

    // Inserir no vetor
    for (int i = 0; i < tamanho; i++) {
        inserir_no_vetor(&repo_vetor, &lista[i]); 
    }

    // Inserir na árvore binária
    for (int i = 0; i < tamanho; i++) {
        raiz_ab = inserir_na_ab(raiz_ab, &lista[i]);
    }

    // Inserir na AVL
    for (int i = 0; i < tamanho; i++) {
        raiz_avl = inserir_na_avl(raiz_avl, &lista[i]);
    }

    // Inserir na AVL por frequência
    for (int i = 0; i < tamanho; i++) {
        raiz_avl_frequencia = inserir_na_avl(raiz_avl_frequencia, &lista[i]);
    }

    printf("Arquivo carregado com sucesso! Tempo total: %.2f segundos\n", tempo);

    free(lista); // já copiamos os dados para as estruturas
}

void buscar_palavra() {
    char palavra[MAX_LEN_PALAVRA];
    printf("Digite a palavra a ser buscada: ");
    scanf("%s", palavra);

    para_minusculo(palavra);

    clock_t inicio, fim;
    double tempo;

    // Vetor
    inicio = clock();
    palavra_busca* resultado_vetor = buscar_no_vetor(&repo_vetor, palavra);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (resultado_vetor) {
        printf("[VETOR] Palavra encontrada: %s | Freq: %d | Tempo: %.6f s\n",
               resultado_vetor->palavra, resultado_vetor->freqTotal, tempo);
    } else {
        printf("[VETOR] Palavra nao encontrada (%.6f s)\n", tempo);
    }

    // Árvore Binária
    inicio = clock();
    palavra_busca* resultado_ab = buscar_na_ab(raiz_ab, palavra);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (resultado_ab) {
        printf("[AB] Palavra encontrada: %s | Freq: %d | Tempo: %.6f s\n",
               resultado_ab->palavra, resultado_ab->freqTotal, tempo);
    } else {
        printf("[AB] Palavra nao encontrada (%.6f s)\n", tempo);
    }

    // AVL
    inicio = clock();
    palavra_busca* resultado_avl = buscar_na_avl(raiz_avl, palavra);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (resultado_avl) {
        printf("[AVL] Palavra encontrada: %s | Freq: %d | Tempo: %.6f s\n",
               resultado_avl->palavra, resultado_avl->freqTotal, tempo);
    } else {
        printf("[AVL] Palavra nao encontrada (%.6f s)\n", tempo);
    }
}

void buscar_por_frequencia() {
    int freq;
    printf("Digite a frequencia a ser buscada: ");
    scanf("%d", &freq);

    clock_t inicio = clock();
    palavra_busca* resultado = buscar_na_avl_por_frequencia(raiz_avl_frequencia, freq);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (resultado) {
        printf("Palavra com frequencia %d encontrada: %s | Tempo: %.6f s\n",
               freq, resultado->palavra, tempo);
    } else {
        printf("Nenhuma palavra encontrada com frequencia %d (%.6f s)\n", freq, tempo);
    }
}