#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool verificaDiag(int side, int **matriz){
    for(int i = 0; i < side; i++){
        for (int j = 0; j < side; j++){
            if (i != j && matriz[i][j] != 0){
                return false;
            }
        }
    }
    return true;
}

void criaMatriz(int linhas, int colunas, int ** matriz){
    srand(time(NULL));
    
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            // Só remover o if para testar com valores 100% aleatórios
            // Do jeito que está 100% das matrizes serão diagonais
            if (i != j){
                matriz[i][j] = 0;
                continue;
            }
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
    
    printf("Digite o tamanho do lado da matriz: ");
    scanf_s("%d", &side);
    
    m = malloc(sizeof(int) * side);
    for(int i = 0; i < side; i++) {
        m[i] = malloc(side * sizeof(int));
    }

    criaMatriz(side, side, m);
    // printMatrix(side, side, m);
    bool x = verificaDiag(side, m);
    x? printf("Eh diagonal\n") : printf("Nao eh diagonal\n");

    for(int i = 0; i < side; i++) {
        free(m[i]);
    }
    free(m);

    return 0;
}