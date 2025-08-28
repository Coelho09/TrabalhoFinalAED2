#ifndef MUSICAS_H
#define MUSICAS_H




typedef struct musicData{ 
    char autor[50];
    char nome[50];
    char estrofe[100];
    float freqs;
} musicData;

typedef struct node {
    char palavra[50];
    musicData dados;
    int qtdRepositorio;
    struct node *left;
    struct node *right;
} Node;


Node *criaNo(char* palavra);
int count_occurrences(char *letra, char *palavra);





#endif
