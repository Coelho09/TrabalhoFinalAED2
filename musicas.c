#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicas.h"


#define MAX_LINE_LEN 2048
#define MAX_LYRICS_LEN 20000 // Aumentado para guardar a letra inteira
#define SNIPPET_LEN 100


int count_occurrences(char *letra, char *palavra) {
    int count = 0;
    const char *temp = letra;
    while((temp = strstr(temp, palavra))) {
        count++;
        temp++; 
    }
    return count;
}

// Função principal que processa a busca no arquivo
void buscar_musica(char *arq,Node *node) {
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE_LEN];
    char music_title[MAX_LINE_LEN] = "";
    char composer[MAX_LINE_LEN] = "";
    char full_lyrics[MAX_LYRICS_LEN] = "";
    char current_stanza[MAX_LYRICS_LEN] = "";
    char stanza_with_palavra[MAX_LYRICS_LEN] = "";
    int palavra_found_in_song = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Verifica se a linha é de título ou se é uma linha em branco
        char *delimiter = strstr(line, "–");
        int is_blank_line = (strlen(line) <= 1 && (line[0] == '\n' || line[0] == '\r'));

        // Se for uma nova música (ou o fim do arquivo), processa a música anterior
        if (delimiter != NULL || feof(file)) {
            if (music_title[0] != '\0' && palavra_found_in_song) {
                int total_count = count_occurrences(full_lyrics, node->palavra);
                
                printf("%s – %s – ", music_title, composer);
                // Imprime os primeiros 100 caracteres da estrofe
                int len = strlen(stanza_with_palavra);
                for (int i = 0; i < len && i < SNIPPET_LEN; i++) {
                    putchar(stanza_with_palavra[i]);
                }
                if (len > SNIPPET_LEN) {
                    printf("...");
                }
                printf(" – %d\n", total_count);
            }

            // Reseta as variáveis para a próxima música
            full_lyrics[0] = '\0';
            current_stanza[0] = '\0';
            stanza_with_palavra[0] = '\0';
            palavra_found_in_song = 0;

            // Se for uma linha de título, extrai as informações
            if (delimiter != NULL) {
                int title_len = delimiter - line;
                strncpy(music_title, line, title_len);
                music_title[title_len] = '\0';
                // Remove espaços em branco do final
                for (int i = title_len - 1; i >= 0 && (music_title[i] == ' ' || music_title[i] == '\t'); i--) {
                    music_title[i] = '\0';
                }
                strcpy(composer, delimiter + 2);
                composer[strcspn(composer, "\n")] = 0; // Remove quebra de linha
            }
        } else if (music_title[0] != '\0') { // Se for linha de letra
            // Adiciona a linha na letra completa e na estrofe atual
            strncat(full_lyrics, line, sizeof(full_lyrics) - strlen(full_lyrics) - 1);
            strncat(current_stanza, line, sizeof(current_stanza) - strlen(current_stanza) - 1);

            // Se a palavra-chave for encontrada e ainda não tivermos uma estrofe guardada
            if (strstr(line, node->palavra) != NULL && !palavra_found_in_song) {
                palavra_found_in_song = 1;
            }

            // Se for uma linha em branco, a estrofe terminou
            if (is_blank_line) {
                 // Se a estrofe continha a palavra-chave e ainda não salvamos uma, salve-a.
                if (strstr(current_stanza, node->palavra) != NULL && stanza_with_palavra[0] == '\0') {
                    strcpy(stanza_with_palavra, current_stanza);
                    // Remove quebras de linha do snippet para melhor formatação
                    for(int i = 0; stanza_with_palavra[i] != '\0' && i < SNIPPET_LEN + 20; i++) {
                        if(stanza_with_palavra[i] == '\n' || stanza_with_palavra[i] == '\r') {
                            stanza_with_palavra[i] = ' ';
                        }
                    }
                }
                current_stanza[0] = '\0'; // Reseta a estrofe atual
            }
        }
    }
    
    // Processa a última música do arquivo
    if (music_title[0] != '\0' && palavra_found_in_song) {
        // Se a última estrofe continha a palavra e nenhuma outra foi salva
        if (strstr(current_stanza, node->palavra) != NULL && stanza_with_palavra[0] == '\0') {
            strcpy(stanza_with_palavra, current_stanza);
            for(int i = 0; stanza_with_palavra[i] != '\0' && i < SNIPPET_LEN + 20; i++) {
                if(stanza_with_palavra[i] == '\n' || stanza_with_palavra[i] == '\r') {
                    stanza_with_palavra[i] = ' ';
                }
            }
        }
        int total_count = count_occurrences(full_lyrics, node->palavra);
        printf("%s – %s – ", music_title, composer);
        int len = strlen(stanza_with_palavra);
        for (int i = 0; i < len && i < SNIPPET_LEN; i++) {
            putchar(stanza_with_palavra[i]);
        }
        if (len > SNIPPET_LEN) {
            printf("...");
        }
        printf(" – %d\n", total_count);
    }


    fclose(file);
}

Node* criaNo(char *palavra) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->palavra, palavra);
    newNode->left = newNode->right = NULL;
     
    
    return newNode;
}





Node* insert(Node* node, char * palavra) {
  
    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(palavra);
    
    // If the key is already present in the tree,
    // return the node
    if (strcmp(node->palavra, palavra) == 0)
        return node;
    
    // Otherwise, recur down the tree. If the key 
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (strcmp(node->palavra,palavra) < 0)
        node->right = insert(node->right, palavra);
  
    // If the key to be inserted is smaller than 
    // the node's key,insert it in the left subtree
    else
        node->left = insert(node->left, palavra);

    // Return the (unchanged) node pointer
    return node;
}


