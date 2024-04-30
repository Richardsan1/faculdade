#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int val = rand() % 100 + 1;

    int opt, chance = 1;
    printf("Digite um número: ");
    scanf("%d", &opt);


    while (opt != val && chance < 5) {
        if (opt >= 1 && opt <= 100) {
            if (opt > val) {
                printf("você chutou muito alto\n");
            } else {
                printf("você chutou muito baixo\n");
            }
            chance++;
        } else {
            printf("número inválido\n");
        }
        printf("Digite outro número: ");
        scanf("%d", &opt);
    }
    if (chance == 5){
        printf("você excedeu o número máximo de tentativas, número correto: %d\n", val);
    } else {
        printf("Parabéns você acertou!!!\n");
        printf("%d tentativas\n", chance);
    }
    return 0;
}