#include "processa_arquivos.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "avl-tree.h"
#include "binary-tree.h"
#include "binary_search.h"

void carregar_arquivos_em_estruturas(const char* nome_arquivo, RepositorioVetor* vetor, NoAB** raiz_ab, NoAVL** raiz_avl) {
    FILE *file = fopen(nome_arquivo, "r");
    char linha[256];
    int linha_atual = 0;
    char estrofe_cache[101] = ""; // Armazena a primeira estrofe para o "contexto"

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nome_arquivo);
        return;
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), file) != NULL) {
        // Remove o caractere de nova linha '\n'
        linha[strcspn(linha, "\n")] = '\0';

        // Usa a primeira linha como a estrofe de contexto
        if (linha_atual == 0) {
            strncpy(estrofe_cache, linha, 100);
            estrofe_cache[100] = '\0'; // Garante o terminador nulo
        }

        // Divide a linha em palavras usando strtok
        char *palavra_token = strtok(linha, " ,.?!;:\n\r");
        
        while (palavra_token != NULL) {
            // Cria uma cópia da palavra para não modificar a string original
            char palavra_limpa[50];
            strcpy(palavra_limpa, palavra_token);

            // Normaliza a palavra: converte para minúsculas e remove pontuação
            para_minusculo(palavra_limpa);
            limpar_string(palavra_limpa);
            
            // Verifica se a palavra não ficou vazia após a limpeza
            if (strlen(palavra_limpa) > 0) {
                palavra_busca nova_entrada;
                strcpy(nova_entrada.palavra, palavra_limpa);
                
                // Preenche os dados da música. 
                // A implementação real precisaria de uma forma de extrair
                // o nome da música e do compositor do arquivo de texto ou metadados.
                strcpy(nova_entrada.mData.nomeMus, "Exemplo de Musica");
                strcpy(nova_entrada.mData.compo, "Exemplo de Compositor");
                strcpy(nova_entrada.mData.estrofe, estrofe_cache);
                nova_entrada.mData.frequencia = 1;
                nova_entrada.freqTotal = 1;
                
                // --- Lógica de Inserção nas Estruturas ---
                
                // 1. Inserção no Vetor
                // As funções de inserção devem verificar se a palavra já existe e,
                // em caso afirmativo, apenas atualizar as frequências.
                inserir_no_vetor(vetor, nova_entrada);

                // 2. Inserção na Árvore Binária de Busca
                *raiz_ab = inserir_na_ab(*raiz_ab, &nova_entrada);

                // 3. Inserção na Árvore AVL
                *raiz_avl = inserir_na_avl(*raiz_avl, nova_entrada);
            }
            
            // Pega a próxima palavra na linha
            palavra_token = strtok(NULL, " ,.?!;:\n\r");
        }
        linha_atual++;
    }

    fclose(file);
    printf("Arquivo '%s' processado com sucesso.\n", nome_arquivo);
    printf("Total de palavras no repositório (vetor): %d\n", vetor->tamanho);
}
