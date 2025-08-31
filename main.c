

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "repositorio.h"
#include "binary_search.h"
#include "binary-tree.h"
#include "avl-tree.h"
#include "utils.h"
#include "processa_arquivos.h"


#define NUM_REPETICOES_BUSCA 10000

void menu_principal();
void carregar_arquivos();
void buscar_palavra();
void buscar_por_frequencia();

RepositorioVetor repo_vetor;
NoAB* raiz_ab = NULL;
NoAVL* raiz_avl = NULL;
NoAVL* raiz_avl_frequencia = NULL;

int main() {
    inicializa_vetor(&repo_vetor);
    int opcao;
    do {
        menu_principal();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1;
            continue;
        }
        getchar(); // Consome o '\n' deixado pelo scanf

        switch (opcao) {
            case 1: carregar_arquivos(); break;
            case 2: buscar_palavra(); break;
            case 3: buscar_por_frequencia(); break;
            case 0: printf("Fim!\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
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
    
    liberar_vetor(&repo_vetor);
    liberar_ab(raiz_ab);
    liberar_avl(raiz_avl);
    liberar_avl(raiz_avl_frequencia);
    
    
    inicializa_vetor(&repo_vetor);
    raiz_ab = NULL;
    raiz_avl = NULL;
    raiz_avl_frequencia = NULL;

    char nome_arquivo[256];
    printf("Digite o nome do arquivo de musica (.txt): ");
    scanf("%255s", nome_arquivo);

    int tamanho = 0;
    palavra_busca* lista = processa_arquivo(nome_arquivo, &tamanho);

    if (lista == NULL) {
        printf("Erro ao processar o arquivo!\n");
        return;
    }
    printf("Arquivo carregado com sucesso! Processando %d palavras...\n", tamanho);

    clock_t inicio, fim;
    double tempo;

    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        inserir_no_vetor(&repo_vetor, &lista[i]);
    }
    shell_sort_vetor(&repo_vetor, repo_vetor.tamanho);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de insercao no VETOR + SORT: %.14f s\n", tempo);


    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        raiz_ab = inserir_na_ab(raiz_ab, &lista[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na ARVORE BINARIA: %.14f s\n", tempo);

    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        raiz_avl = inserir_na_avl(raiz_avl, &lista[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na ARVORE AVL (palavra): %.14f s\n", tempo);

    
    inicio = clock();
    for (int i = 0; i < tamanho; i++) {
        raiz_avl_frequencia = inserir_na_avl_freq(raiz_avl_frequencia, &lista[i]);
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de insercao na ARVORE AVL (frequencia): %.14f s\n", tempo);

    printf("Estruturas carregadas! %d palavras unicas encontradas.\n", repo_vetor.tamanho);
    free(lista);
}

void buscar_palavra() {
    if (repo_vetor.tamanho == 0) {
        printf("Nenhum arquivo carregado. Use a opcao 1 primeiro.\n");
        return;
    }
    char palavra[MAX_LEN_PALAVRA];
    printf("Digite a palavra a ser buscada: ");
    scanf("%99s", palavra);
    para_minusculo(palavra);

    clock_t inicio, fim;
    double tempo_total, tempo_medio;
    palavra_busca* resultado = NULL;

    // --- VETOR ---
    inicio = clock();
    for(int i = 0; i < NUM_REPETICOES_BUSCA; ++i) {
        resultado = buscar_no_vetor(&repo_vetor, palavra);
    }
    fim = clock();
    tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_medio = tempo_total / NUM_REPETICOES_BUSCA;
    
    if (resultado) {
        printf("\n--- VETOR ---\n");
        printf("Palavra: %s\n", resultado->palavra);
        printf("Frequencia Total: %d\n", resultado->freqTotal);
        printf("Nome da Musica: %s\n", resultado->mData.nomeMus);
        printf("Compositor: %s\n", resultado->mData.compo);
        printf("Estrofe: %.100s...\n", resultado->mData.estrofe);
        printf("Tempo medio de busca: %.14f s (em %d repeticoes)\n", tempo_medio, NUM_REPETICOES_BUSCA);
    } else {
        printf("[VETOR] Palavra nao encontrada (Tempo medio: %.14f s)\n", tempo_medio);
    }

    // --- ÁRVORE BINÁRIA ---
    inicio = clock();
    for(int i = 0; i < NUM_REPETICOES_BUSCA; ++i) {
        resultado = buscar_na_ab(raiz_ab, palavra);
    }
    fim = clock();
    tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_medio = tempo_total / NUM_REPETICOES_BUSCA;

    if (resultado) {
        printf("\n--- ARVORE BINARIA ---\n");
        printf("Palavra: %s\n", resultado->palavra);
        printf("Frequencia Total: %d\n", resultado->freqTotal);
        printf("Nome da Musica: %s\n", resultado->mData.nomeMus);
        printf("Compositor: %s\n", resultado->mData.compo);
        printf("Estrofe: %.100s...\n", resultado->mData.estrofe);
        printf("Tempo medio de busca: %.14f s (em %d repeticoes)\n", tempo_medio, NUM_REPETICOES_BUSCA);
    } else {
        printf("[AB] Palavra nao encontrada (Tempo medio: %.14f s)\n", tempo_medio);
    }

    // --- ÁRVORE AVL ---
    inicio = clock();
    for(int i = 0; i < NUM_REPETICOES_BUSCA; ++i) {
        resultado = buscar_na_avl(raiz_avl, palavra);
    }
    fim = clock();
    tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_medio = tempo_total / NUM_REPETICOES_BUSCA;

    if (resultado) {
        printf("\n--- ARVORE AVL ---\n");
        printf("Palavra: %s\n", resultado->palavra);
        printf("Frequencia Total: %d\n", resultado->freqTotal);
        printf("Nome da Musica: %s\n", resultado->mData.nomeMus);
        printf("Compositor: %s\n", resultado->mData.compo);
        printf("Estrofe: %.100s...\n", resultado->mData.estrofe);
        printf("Tempo medio de busca: %.14f s (em %d repeticoes)\n", tempo_medio, NUM_REPETICOES_BUSCA);
    } else {
        printf("[AVL] Palavra nao encontrada (Tempo medio: %.14f s)\n", tempo_medio);
    }
}

void buscar_por_frequencia() {
    if (raiz_avl_frequencia == NULL) {
        printf("Nenhum arquivo carregado. Use a opcao 1 primeiro.\n");
        return;
    }
    int freq;
    printf("Digite a frequencia a ser buscada: ");
    if (scanf("%d", &freq) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    
    clock_t inicio, fim;
    double tempo_total, tempo_medio;
    palavra_busca* resultado = NULL;
    
    inicio = clock();
    for(int i = 0; i < NUM_REPETICOES_BUSCA; ++i) {
        resultado = buscar_na_avl_por_frequencia(raiz_avl_frequencia, freq);
    }
    fim = clock();
    tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempo_medio = tempo_total / NUM_REPETICOES_BUSCA;
    
    if (resultado) {
        printf("\n--- RESULTADO DA BUSCA POR FREQUENCIA ---\n");
        printf("Frequencia buscada: %d\n", freq);
        printf("Palavra encontrada: %s\n", resultado->palavra);
        printf("Frequencia Total: %d\n", resultado->freqTotal);
        printf("Nome da Musica: %s\n", resultado->mData.nomeMus);
        printf("Compositor: %s\n", resultado->mData.compo);
        printf("Estrofe: %.100s...\n", resultado->mData.estrofe);
        printf("Tempo medio de busca: %.14f s (em %d repeticoes)\n", tempo_medio, NUM_REPETICOES_BUSCA);
    } else {
        printf("Nenhuma palavra encontrada com frequencia %d (Tempo medio: %.14f s)\n", freq, tempo_medio);
    }
}
