#include "utils.h"
#include <ctype.h>
#include <string.h>

void para_minusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }   
}

void remove_acento(char *str) {
    for (int i = 0; str[i]; i++){
        switch(str[i]) {
            case 'á': case 'à': case 'ã': case 'â': case 'ä': str[i] = 'a'; break;
            case 'Á': case 'À': case 'Ã': case 'Â': case 'Ä': str[i] = 'A'; break;
            case 'é': case 'è': case 'ê': case 'ë': str[i] = 'e'; break;
            case 'É': case 'È': case 'Ê': case 'Ë': str[i] = 'E'; break;
            case 'í': case 'ì': case 'î': case 'ï': str[i] = 'i'; break;
            case 'Í': case 'Ì': case 'Î': case 'Ï': str[i] = 'I'; break;
            case 'ó': case 'ò': case 'õ': case 'ô': case 'ö': str[i] = 'o'; break;
            case 'Ó': case 'Ò': case 'Õ': case 'Ô': case 'Ö': str[i] = 'O'; break;
            case 'ú': case 'ù': case 'û': case 'ü': str[i] = 'u'; break;
            case 'Ú': case 'Ù': case 'Û': case 'Ü': str[i] = 'U'; break;
            case 'ç': str[i] = 'c'; break;
            case 'Ç': str[i] = 'C'; break;
        }
    }
}

// "limpa" o caractere atual da string
void limpar_string(char *str) {
    int i, j = 0;

    remove_acento(str);

    for (i = 0; str[i] != '\0'; i++){
        char c = str[i];
        if (isalnum((unsigned char)c) || c == ' '){
            str[j++] = c;
        }
    }
    str[j] = '\0';

    para_minusculo(str);
}
