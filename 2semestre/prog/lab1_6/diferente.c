#include <stdio.h>
#include <stdlib.h>

int diferente(int v[], int n){
    int qtd =0, sizeAux = 0;
    int * aux = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        int exist = 0;
        
        for (int j =0; j < sizeAux; j++){
            if (aux[j] == v[i]){
                exist = 1;
                break;
            }
        }
        if (!exist){
            aux[sizeAux] = v[i];
            sizeAux++;
            qtd++;
        }
    }

    free(aux);
    return qtd;
}

int main(){
    int v[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    printf("%d\n", diferente(v, 10));
}