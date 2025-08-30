#include "repositorio.h"


typedef struct {
    palavra_busca* vetor;
    int tamanho;
    int capacidade;
} RepositorioVetor;

void inicializar_vetor(RepositorioVetor* rv);
void inserir_no_vetor(RepositorioVetor* rv, palavra_busca * nova_entrada);
palavra_busca* buscar_no_vetor(RepositorioVetor* rv, char* palavra);
void ordenar_vetor_alfabeticamente(RepositorioVetor* rv);
void liberar_vetor(RepositorioVetor* rv);
void shell_sort_vetor(RepositorioVetor  *rv, int vec_size);
int buscar_no_vetor_indice(RepositorioVetor* rv, char* palavra);