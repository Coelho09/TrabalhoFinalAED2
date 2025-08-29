#ifndef PROCESSA_ARQUIVOS_H
#define PROCESSA_ARQUIVOS_H

#include "musicas.h" // Inclui os cabeçalhos das estruturas de dados

// Lê um arquivo de música e processa as palavras para as estruturas de dados
void carregar_arquivos_em_estruturas(const char* nome_arquivo, RepositorioVetor* vetor, NoAB** raiz_ab, NoAVL** raiz_avl);

#endif