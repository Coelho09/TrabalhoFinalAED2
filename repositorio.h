#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#define MAX_LEN_PALAVRA 100
#define MAX_MUSICA_NOME 100
#define MAX_COMPOSITOR_NOME 100
#define MAX_ESTROFE 101

typedef struct musicaDados {
    char nomeMus[MAX_MUSICA_NOME];
    char compo[MAX_COMPOSITOR_NOME];
    char estrofe[MAX_ESTROFE];
} musicaDados;

typedef struct palavra_busca {
    char palavra[MAX_LEN_PALAVRA];
    musicaDados mData;
    int freqTotal;
} palavra_busca;

#endif
