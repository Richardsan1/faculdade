#include <stdio.h>

void * minha_strcpy (char *destino , const char *origem) {
    char * p = destino;
    while (*origem != '\0') {
        *p = *origem;
        p++;
        origem++;
    }
    *p = '\0';
}
int main () {
    char str1 [50];
    char str2 [] = "Teste de copia de string";
    minha_strcpy (str1 , str2);
    printf("String copiada: %s\n", str1);
    return 0;
}
