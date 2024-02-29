#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int val = rand() % 100 + 1;

    printf("Digite um número: ");
    int opt, tent = 0; 
    scanf("%d", &opt);
    while (opt != val) {
        if (opt >= 1 && opt <= 100) {
            if (opt > val) {
                printf("você chutou muito alto\n");
            } else {
                printf("você chutou muito baixo\n");
            }
            tent++;
        } else {
            printf("número inválido\n");
        }
        printf("Digite outro número: ");
        scanf("%d", &opt);
    }
    printf("Parabéns você acertou!!!\n");
    printf("%d tentativas\n", tent);
    return 0;
}