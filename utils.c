#include "utils.h"
#include <ctype.h>
#include <string.h>

void para_minusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void trim(char* str) {
    if (str == NULL) {
        return;
    }
    int inicio = 0;
    int fim = strlen(str) - 1;
    while (fim >= 0 && isspace((unsigned char)str[fim])) {
        fim--;
    }
    str[fim + 1] = '\0';
    while (isspace((unsigned char)str[inicio])) {
        inicio++;
    }
    if (inicio > 0) {
        memmove(str, str + inicio, fim - inicio + 2);
    }
}
