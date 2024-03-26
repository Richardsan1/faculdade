#include <stdio.h>

int * inverte(int v[]){
    int tam = 4;
    for (int i =0; i<= tam/2; i ++){
        int temp = v[i];
        v[i] = v[tam-i];
        v[tam-i] = temp;
    }
    return v;
}

int main(){
    int arr[] = {10, 20, 45, 18, 11};
    int * inv = inverte(arr);
    
    printf("[ ");
    for (int i = 0; i < 5; i++){
        printf("%d ", inv[i]);
        if (i != 4){
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}