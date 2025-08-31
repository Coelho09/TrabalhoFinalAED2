#include "processa_arquivos.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

palavra_busca* processa_arquivo(const char* nome_arquivo, int* tamanho) {
    *tamanho = 0;
    palavra_busca* lista_temp = NULL;
    int capacidade_lista = 0;

    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char linha_buffer[1024];
    musicaDados meta_atual;
    int lendo_letra = 0;

    // Detecta o formato do arquivo para compatibilidade
    fpos_t pos_inicial;
    fgetpos(arquivo, &pos_inicial);
    fgets(linha_buffer, sizeof(linha_buffer), arquivo);
    fsetpos(arquivo, &pos_inicial); // Volta para o início

    int formato_consolidado = (strstr(linha_buffer, "=== Música") != NULL);

    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo)) {
        if (formato_consolidado) {
            if (strstr(linha_buffer, "=== Música") != NULL) {
                if (fgets(meta_atual.nomeMus, sizeof(meta_atual.nomeMus), arquivo)) {
                    meta_atual.nomeMus[strcspn(meta_atual.nomeMus, "\n\r")] = 0;
                    trim(meta_atual.nomeMus);
                }
                if (fgets(meta_atual.compo, sizeof(meta_atual.compo), arquivo)) {
                    meta_atual.compo[strcspn(meta_atual.compo, "\n\r")] = 0;
                    trim(meta_atual.compo);
                }
                lendo_letra = 1;
                continue;
            }
        } else if (!lendo_letra) { // Se não for consolidado, lê o cabeçalho uma vez
             strcpy(meta_atual.nomeMus, linha_buffer);
             meta_atual.nomeMus[strcspn(meta_atual.nomeMus, "\n\r")] = 0;
             trim(meta_atual.nomeMus);
             if (fgets(meta_atual.compo, sizeof(meta_atual.compo), arquivo)) {
                meta_atual.compo[strcspn(meta_atual.compo, "\n\r")] = 0;
                trim(meta_atual.compo);
             }
             lendo_letra = 1;
             continue;
        }


        if (lendo_letra) {
            char linha_para_tokenizar[1024];
            strcpy(linha_para_tokenizar, linha_buffer);
            char* token = strtok(linha_para_tokenizar, " \t\n\r,-.!?();:\"'");
            while (token != NULL) {
                para_minusculo(token);
                if (strlen(token) > 2) {
                    int encontrado = 0;
                    for (int j = 0; j < *tamanho; j++) {
                        if (strcmp(lista_temp[j].palavra, token) == 0) {
                            lista_temp[j].freqTotal++;
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado) {
                        if (*tamanho >= capacidade_lista) {
                            capacidade_lista = (capacidade_lista == 0) ? 128 : capacidade_lista * 2;
                            lista_temp = realloc(lista_temp, capacidade_lista * sizeof(palavra_busca));
                        }
                        strcpy(lista_temp[*tamanho].palavra, token);
                        lista_temp[*tamanho].freqTotal = 1;
                        strncpy(lista_temp[*tamanho].mData.estrofe, linha_buffer, MAX_ESTROFE - 1);
                        lista_temp[*tamanho].mData.estrofe[MAX_ESTROFE - 1] = '\0';
                        strcpy(lista_temp[*tamanho].mData.nomeMus, meta_atual.nomeMus);
                        strcpy(lista_temp[*tamanho].mData.compo, meta_atual.compo);
                        (*tamanho)++;
                    }
                }
                token = strtok(NULL, " \t\n\r,-.!?();:\"'");
            }
        }
    }

    fclose(arquivo);
    return lista_temp;
}






