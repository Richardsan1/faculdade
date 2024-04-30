// Desenvolva um programa que:
// • Sorteie um número inteiro no intervalo de 1 a 100 (incluindo os valores 1 e
// 100).
// • Solicite que o usuário tente adivinhar o número sorteado, digitando o seu
// palpite.
// (se o usuário entrar um valor inválido - menor que 1 ou maior que 100 - o
// programa deverá refazer a solicitação até que o usuário entre um valor
// válido).
// • Verifique se o palpite do usuário está correto:
// • Se estiver correto, o programa deverá imprimir na tela “Parabéns!!! Você acertou!”
// • Se o palpite for menor que o número sorteado, deverá imprimir “Você chutou muito baixo! O
// valor correto é xx.” (onde xx é o número sorteado).
// • Se o palpite for maior que o número sorteado, deverá imprimir “Você chutou muito alto! O valor
// correto é xx.” (onde xx é o número sorteado).
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int val = rand() % 100 + 1;

    printf("Digite um número: ");
    int opt; 
    scanf("%d", &opt);
    while (0) {
        if (opt < 1 || opt > 100) {
            printf("número inválido\n");
        }
    }

    if (opt > val){
        printf("Você chutou muito alto! O valor correto é %d.\n", val);
    } else if (opt < val) {
        printf("Você chutou muito baixo! O valor correto é %d.\n", val);
    } else {
        printf("Parabéns!!! Você acertou!\n");
    }

    return 0;
}