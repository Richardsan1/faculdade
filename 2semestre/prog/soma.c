#include <stdio.h>

float soma(float n1, float n2, float n3){
    return n1+n2+n3;
}

int main(){
    float n1, n2, n3;
    printf("digite o primeiro numero: ");
    scanf("%f", &n1);
    printf("digite o segundo numero: ");
    scanf("%f", &n2);
    printf("digite o terceiro numero: ");
    scanf("%f", &n3);

    printf("a soma dos numeros eh igual a: %.2f\n", soma(n1, n2, n3));
    return 0;
}