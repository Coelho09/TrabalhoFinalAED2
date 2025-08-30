#include "processa_arquivos.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl-tree.h"

#include "binary-tree.h"
#include "binary_search.h"

palavra_busca* processa_arquivo(const char* nome_arquivo, int* tamanho) {
    *tamanho = 0; // começa vazio
    palavra_busca* lista_temp = NULL;
    char caminho_completo[512];
    char *diretorio_base = "letras-mus/";
    snprintf(caminho_completo, sizeof(caminho_completo), "%s%s", diretorio_base, nome_arquivo);

    FILE* arquivo = fopen(caminho_completo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    musicaDados meta;
    // Lê cabeçalho
    fgets(meta.nomeMus, sizeof(meta.nomeMus), arquivo);
    meta.nomeMus[strcspn(meta.nomeMus, "\n")] = 0;
    trim(meta.nomeMus);

    fgets(meta.compo, sizeof(meta.compo), arquivo);
    meta.compo[strcspn(meta.compo, "\n")] = 0;
    trim(meta.compo);

    char buffer_pula_linha[256];
    fgets(buffer_pula_linha, sizeof(buffer_pula_linha), arquivo); // pula linha em branco

    char linha_buffer[1024];
    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo) != NULL) {
        char linha_para_tokenizar[1024];
        strcpy(linha_para_tokenizar, linha_buffer);

        char* token = strtok(linha_para_tokenizar, " \t\n\r,-.!?();:\"'");
        while (token != NULL) {
            para_minusculo(token);
            if (strlen(token) > 3) {
                int encontrado = 0;
                for (int j = 0; j < *tamanho; j++) {
                    if (strcmp(lista_temp[j].palavra, token) == 0) {
                        lista_temp[j].freqTotal++;
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    lista_temp = realloc(lista_temp, (*tamanho + 1) * sizeof(palavra_busca));
                    strcpy(lista_temp[*tamanho].palavra, token);
                    lista_temp[*tamanho].freqTotal = 1;

                    // Guarda metadados no mData
                    strncpy(lista_temp[*tamanho].mData.estrofe, linha_buffer, MAX_ESTROFE-1);
                    lista_temp[*tamanho].mData.estrofe[MAX_ESTROFE-1] = '\0';

                    strcpy(lista_temp[*tamanho].mData.nomeMus, meta.nomeMus);
                    strcpy(lista_temp[*tamanho].mData.compo, meta.compo);

                    (*tamanho)++;
                }
            }
            token = strtok(NULL, " \t\n\r,-.!?();:\"'");
        }
    }

    fclose(arquivo);
    return lista_temp;
}