#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int soma(int side, int **matriz){
    int sum = 0;
    for(int i = 0; i < side; i++){
        sum += matriz[i][i];
    }
    return sum;
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
    int side;
    int **m;
    
    printf("Digite o tamanho da matriz: ");
    scanf_s("%d", &side);
    
    
    m = malloc(sizeof(int) * side);
    for(int i = 0; i < side; i++) {
        m[i] = malloc(side * sizeof(int));
    }

    criaMatriz(side, side, m);
    // printMatrix(side, side, m);
    int x = soma(side, m);
    printf("traco: %d", x);
    
    for(int i = 0; i < side; i++) {
        free(m[i]);
    }
    free(m);

    return 0;
}