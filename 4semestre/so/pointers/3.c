#include <stdio.h>
#include <stdlib.h>

int main () {
    int *vetor;
    int tamanho;
    float media = 0;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    // Aloque memória para o vetor
    // Seu código aqui
    // Verifique se a alocação foi bem-sucedida
    // Preencha o vetor
    vetor = malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }


    printf("Digite os %d valores:\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
        media += vetor[i];
    }
    // Calcule a média
    media = media / tamanho;
    printf("Media dos valores: %.2f\n", media);
    // Libere a memória
    // Seu código aqui
    free(vetor);
    return 0;
}