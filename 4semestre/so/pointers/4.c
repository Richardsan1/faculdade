#include <stdio.h>
#include <stdlib.h>

int main () {
    int ** matriz;
    int linhas , colunas;
    printf("Digite o numero de linhas: ");
    scanf("%d", &linhas);
    printf("Digite o numero de colunas: ");
    scanf("%d", &colunas);
    // Aloque memória para a matriz
    // Seu código aqui
    // Verifique se a alocação foi bem-sucedida
    // Preencha a matriz

    matriz = malloc(linhas * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memoria\n");
            return 1;
        }
    }

    printf("Digite os valores da matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    // Imprima a matriz
    printf("\nMatriz digitada:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    // Libere a memória - atenção à ordem!
    // Seu código aqui
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return 0;
}