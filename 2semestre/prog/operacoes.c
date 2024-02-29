// Escreva um programa em C que solicite que o usuário forneça dois números
// inteiros e imprima o resultado da soma, subtração, multiplicação e divisão
// inteira desses números.
#include <stdio.h>

int main(){
    int n1, n2;

    printf("escolha o primeiro numero: ");
    scanf("%d", &n1);
    printf("escolha o segundo numero: ");
    scanf("%d", &n2);

    printf("%d + %d = %d\n", n1, n2, n1+n2);
    printf("%d - %d = %d\n", n1, n2, n1-n2);
    printf("%d * %d = %d\n", n1, n2, n1*n2);
    printf("%d / %d = %d\n", n1, n2, n1/n2);

    return 0;
}