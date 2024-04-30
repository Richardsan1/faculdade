#include <stdio.h>
#include <stdbool.h>

bool crescente(int v[], int n){
    for (int i = 0; i < n-1; i++){
        if (v[i] > v[i+1]){
            return false;
        }
    }
    return true;
}

int main(){
    int v[5] = {2,1, 3, 4, 5};
    int n = 5;
    if (crescente(v, n)){
        printf("Crescente\n");
    } else {
        printf("Não crescente\n");
    }
    return 0;
}
