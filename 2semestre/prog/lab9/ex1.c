#include <stdio.h>

int conta_digito(int n, int k){
    if (n == k){
        return 1;
    }
    if (n < 10 && n != k){
        return 0;
    }

    return conta_digito(n%10, k) + conta_digito(n/10, k);
}

int main(){
    int num, busc;
    printf("Digite o numero: ");
    scanf_s("%d", &num);
    printf("Digite o valor a ser procurado: ");
    scanf_s("%d", &busc);

    printf("qtd de vezes: %d\n", conta_digito(num, busc));
    return 0;
}