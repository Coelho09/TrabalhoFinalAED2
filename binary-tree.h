
#include "repositorio.h"
typedef struct NoAB {
    musicaDados entrada;
    struct NoAB* esquerda;
    struct NoAB* direita;
} NoAB;

NoAB* inserir_na_ab(NoAB* no, musicaDados nova_entrada);
musicaDados* buscar_na_ab(NoAB* no, const char* palavra);
void liberar_ab(NoAB* no);