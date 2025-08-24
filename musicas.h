#ifndef MUSICAS_H
#define MUSICAS_H


#define MAX_LINE_LEN 2048
#define MAX_LYRICS_LEN 20000 // Aumentado para guardar a letra inteira
#define SNIPPET_LEN 100

typedef struct musicData{ 
    char autor[50];
    char nome[50];
    char estrofe[100];
    float freqs;
} musicData;

typedef struct node {
    char palavra[50];
    musicData dados[100];
    int qtdRepositorio;
    struct node *left;
    struct node *right;
} Node;


Node *criaNo(char* palavra);




#endif
