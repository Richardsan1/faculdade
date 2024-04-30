#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void somaMatriz(int **a, int **b, int **c, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            c[i][j] = a[i][j] + b[i][j];
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
    srand(time(NULL)+  (int)&*matriz);
    
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            matriz[i][j] = rand() % 101;
        }
    } 
}

int main(){
    int **a, **b, **c, n, m;

    printf("digite a quantidade de linhas: ");
    scanf_s("%d", &n);
    printf("digite a quantidade de colunas: ");
    scanf_s("%d", &m);

    a = malloc(sizeof(int) * n);
    b = malloc(sizeof(int) * n);
    c = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        b[i] = malloc(m * sizeof(int));
        c[i] = malloc(m * sizeof(int));
    }

    criaMatriz(n, m, a);
    criaMatriz(n, m, b);
    somaMatriz(a, b, c, n, m);
    
    printMatrix(n,m,a);
    printf("\n");
    printMatrix(n,m,b);
    printf("\n");
    printMatrix(n,m,c);
    printf("\n");

    for(int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}