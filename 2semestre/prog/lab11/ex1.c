#include <stdio.h>

int main() {
    int i = 1234;
    int *p = &i;
    // Imprime o valor de i
    printf("*p = %d\n", *p);
    // Imprime o endereço de i como um inteiro de 64bits
    printf(" p = %ld\n", (long int)p);
    // Imprime o endereço de i, mas dessa vez como um número hexadecimal
    printf(" p = %p\n", (void *)p);
    // Imprime o endereço de p como um número hexadecimal
    printf("&p = %p\n", (void *)&p);
}
