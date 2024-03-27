#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void transposta(int lin, int col, int **A, int **At){
    for(int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            At[j][i] = A[i][j];
        }
    }
}

void criaMatriz(int linhas, int colunas, int ** matriz){
    srand(time(NULL));
    
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            matriz[i][j] = rand() % 101;
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

int main(){
    int col, lin;
    int **m, **mt;
    
    printf("Digite quantas linhas a matriz tera: ");
    scanf_s("%d", &lin);
    printf("Digite quantas colunas a matriz tera: ");
    scanf_s("%d", &col);
    
    m = malloc(sizeof(int) * lin);
    for(int i = 0; i < lin; i++) {
        m[i] = malloc(col * sizeof(int));
    }
    mt = malloc(sizeof(int) * col);
    for(int i = 0; i < col; i++) {
        mt[i] = malloc(lin * sizeof(int));
    }

    criaMatriz(lin, col, m);
    transposta(lin, col, m, mt);
    
    printMatrix(lin, col, m);
    printf("\n");
    printMatrix(col, lin, mt);
    
    for(int i = 0; i < lin; i++) {
        free(m[i]);
    }
    free(m);
    for(int i = 0; i < col; i++) {
        free(mt[i]);
    }
    free(mt);

    return 0;
}