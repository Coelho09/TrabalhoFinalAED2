#ifndef PROCESSA_ARQUIVOS_H
#define PROCESSA_ARQUIVOS_H
#include "repositorio.h"


// Lê um arquivo de música e processa as palavras para as estruturas de dados
palavra_busca* processa_arquivo(const char* nome_arquivo, int* tamanho);

#endif