#include "binary-tree.h"
#include <stdlib.h>
#include <string.h>




 NoAB* newNodeAB(palavra_busca * newNode) {   
        NoAB* temp = 
       (NoAB*)malloc(sizeof(NoAB));
    temp->entrada = *newNode;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

NoAB* inserir_na_ab(NoAB* no, palavra_busca *nova_entrada) {
    
    NoAB * insert_node = newNodeAB(nova_entrada);


    if (no == NULL)
        return insert_node;
    
     
    if (strcmp(no->entrada.palavra, insert_node->entrada.palavra) == 0){
        if(no->entrada.mData.frequencia < insert_node->entrada.mData.frequencia){
            no->entrada = insert_node->entrada;
        }
    }
        
    
    
    if (strcmp(no->entrada.palavra, insert_node->entrada.palavra) < 0)
        no->direita = inserir_na_ab(no->direita, &insert_node->entrada);
    
    
    else
        no->esquerda = inserir_na_ab(no->esquerda, &insert_node->entrada);

    
    return no;
}




palavra_busca* buscar_na_ab(NoAB* no, char* palavra) {
    

    
      NoAB* curr = no;
    
    while (curr != NULL) {
        
        
        if (strcmp(curr->entrada.palavra, palavra) == 0)
            return &(curr->entrada);
            
         //curr->data < x
        else if (strcmp(curr->entrada.palavra, palavra) < 0) 
            curr = curr->direita;
            
        // Search in left subtree
        else
            curr = curr->esquerda;
    }
    
    
    return NULL;
}


void liberar_ab(NoAB* no) {
    if (no != NULL) {
        liberar_ab(no->esquerda);
        liberar_ab(no->direita);
        free(no);
    }
}