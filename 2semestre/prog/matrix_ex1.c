#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int verificaMaior(int linhas, int colunas, int **matriz){
    int maior = matriz[0][0];
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            if (maior < matriz[i][j]){
                maior = matriz[i][j];
            }
        }
    }
    return maior;
}
void criaMatriz(int linhas, int colunas, int ** matriz){
    srand(time(NULL));
    
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            matriz[i][j] = rand() % 101;
        }
    } 
}

// void printMatrix(int lin, int col, int **m) {
//     for(int i = 0; i < lin; i++) {
//         for(int j = 0; j < col; j++) {
//             printf("%d ", m[i][j]);
//         }
//         printf("\n");
//     }
// }

int main(){
    int col, lin;
    int **m;
    
    printf("Digite quantas linhas a matriz tera: ");
    scanf_s("%d", &lin);
    printf("Digite quantas colunas a matriz tera: ");
    scanf_s("%d", &col);
    
    m = malloc(sizeof(int) * lin);
    for(int i = 0; i < lin; i++) {
        m[i] = malloc(col * sizeof(int));
    }

    criaMatriz(lin, col, m);
    int x = verificaMaior(lin, col, m);

    // printMatrix(lin, col, m);
    
    printf("%d\n", x);
    
    for(int i = 0; i < lin; i++) {
        free(m[i]);
    }
    free(m);

    return 0;
}