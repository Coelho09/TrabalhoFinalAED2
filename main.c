#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para medir o tempo de execução [cite: 35, 39]

#include "repositorio.h"
#include "binary_search.h"
#include "binary-tree.h"
#include "avl-tree.h"
#include "utilidades.h" // Um módulo para funções como 'para_minusculo' e 'limpar_string'

// Funções para a interação com o usuário
void menu_principal();
void carregar_arquivos();
void buscar_palavra();
void buscar_por_frequencia();

// Estruturas globais (ou passadas por parâmetro)
RepositorioVetor repo_vetor;
NoAB* raiz_ab = NULL;
NoAVL* raiz_avl = NULL;
NoAVL* raiz_avl_frequencia = NULL;

int main() {
    inicializar_vetor(&repo_vetor);

    int opcao;
    do {
        menu_principal();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

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
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberar_vetor(&repo_vetor);
    liberar_ab(raiz_ab);
    liberar_avl(raiz_avl);
    liberar_avl(raiz_avl_frequencia); // Libera a árvore de frequência

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

    clock_t inicio_vetor = clock();
    // Processar arquivo e inserir no vetor
    // ...
    clock_t fim_vetor = clock();
    double tempo_vetor = (double)(fim_vetor - inicio_vetor) / CLOCKS_PER_SEC;
    printf("Tempo para carregar no vetor: %.2f segundos\n", tempo_vetor);

    // O mesmo para as arvores AB e AVL
    // ...
}

void buscar_palavra() {
    char palavra_busca[MAX_LEN_PALAVRA];
    printf("Digite a palavra a ser buscada: ");
    scanf("%s", palavra_busca);

    // Converte e limpa a palavra antes da busca
    para_minusculo(palavra_busca);

    // Iniciar e parar cronômetros para cada busca
    // Chamar as funcoes de busca:
    // buscar_no_vetor(...)
    // buscar_na_ab(...)
    // buscar_na_avl(...)
    
    // Exibir os resultados para cada busca, juntamente com o tempo de processamento[cite: 39].
}

void buscar_por_frequencia() {
    // Implemente a construção e busca na árvore AVL por frequência, conforme o requisito[cite: 40].
    // A árvore deve ser construída uma vez a partir dos dados existentes.
}