#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_search.h"

void inicializa_vetor(RepositorioVetor* rv){
    rv->tamanho=0;
    rv->capacidade = 100;
    rv->vetor = (RepositorioVetor *) malloc (rv->capacidade * sizeof(RepositorioVetor));


}


void inserir_no_vetor(RepositorioVetor *rv, palavra_busca nova_musica){
    if (rv->tamanho != 0){
        if (rv->tamanho >= rv->capacidade)
        {
             rv->vetor = (RepositorioVetor *) realloc (rv, sizeof(RepositorioVetor) * (rv->capacidade + 1));
        }
        
            shell_sort_vetor(rv, rv->tamanho);
            if(buscar_no_vetor_indice(rv, nova_musica.palavra) == -1)
            {
                rv->vetor[rv->tamanho] = nova_musica;
                rv->tamanho++;
            } 
            else 
            {
                int pivot =buscar_no_vetor_indice(rv, nova_musica.palavra);
                rv->vetor[pivot] = nova_musica;
            }
    


    } else {
        rv->vetor[rv->tamanho] = nova_musica;
        rv->tamanho++;
    }

}


palavra_busca* buscar_no_vetor(RepositorioVetor* rv, char* palavra) {
  
    int low = 0;
    int high = rv->tamanho - 1 ;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        
        if (strcmp(rv->vetor[mid].palavra, palavra) ==0)
            return &rv->vetor[mid];

        
        if (strcmp(rv->vetor[mid].palavra, palavra ) < 0)
            low = mid + 1;

        
        else
            high = mid - 1;
    }

    
    return NULL;

}



int buscar_no_vetor_indice(RepositorioVetor* rv, char* palavra) {
  
    int low = 0;
    int high = rv->tamanho - 1 ;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        
        if (strcmp(rv->vetor[mid].palavra, palavra) ==0)
            return mid;

        
        if (strcmp(rv->vetor[mid].palavra, palavra ) < 0)
            low = mid + 1;

        
        else
            high = mid - 1;
    }

    
    return -1;

}







void shell_sort_vetor(RepositorioVetor  *rv, int vec_size){
    int i, j, h =1;
    palavra_busca aux; 
    do { h = h * 3 + 1;} while( h<vec_size);
    do {
        h/=3; 
        for(i = h; i < vec_size; i++){
            aux = rv->vetor[i];
            j = i;
            while(strcmp(rv->vetor[j-h].palavra, aux.palavra) > 0){
                rv->vetor[j] = rv->vetor[j-1]; 
                j-=h;
                if(j<h) break;
            }
            rv->vetor[j] = aux;
        } 
    } while(h !=1);

}



void liberar_vetor(RepositorioVetor* rv) {
    free(rv->vetor);
    rv->vetor = NULL;
    rv->tamanho = 0;
    rv->capacidade = 0;
}
