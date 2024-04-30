#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void multiplyMatrices(int n, int m, int p, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int lin, int col, int **m) {
    for(int i = 0; i < lin; i++) {
        for(int j = 0; j < col; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void criaMatriz(int linhas, int colunas, int ** matriz){
    srand(time(NULL)+ (int)&*matriz);
    
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            matriz[i][j] = rand() % 101;
        }
    } 
}

int main() {
    int n, m, p;

    printf("Digite o número de linhas para a matriz A: ");
    scanf_s("%d", &n);
    printf("Digite o número de colunas para a matriz A / linhas para a matriz B: ");
    scanf_s("%d", &m);
    printf("Digite o número de colunas para a matriz B: ");
    scanf_s("%d", &p);

    int **A = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        A[i] = malloc(m * sizeof(int));
    }
    criaMatriz(n, m, A);
    printf("Matrix A:\n");
    printMatrix(n, m, A);

    int **B = malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++) {
        B[i] = malloc(p * sizeof(int));
    }
    criaMatriz(m, p, B);
    printf("Matrix B:\n");
    printMatrix(m, p, B);

    int **C = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        C[i] = malloc(p * sizeof(int));
    }

    multiplyMatrices(n, m, p, A, B, C);
    printf("Matrix C:\n");
    printMatrix(n, p, C);

    for(int i = 0; i < n; i++) {
        free(A[i]);
        free(C[i]);
    }
    for(int i = 0; i < m; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}