#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 30

int busca_seq_rec(int arr[], int lenght, int index, int num){
    if (index == lenght-1){
        return -1;
    }
    if (arr[index] == num){
        return index;
    }
    return busca_seq_rec(arr, lenght, index+1, num);
}

int main(){
    srand(time(NULL));
    int arr[ARRAY_SIZE], num;
    printf("[ ");
    for (int i = 0; i < ARRAY_SIZE; i++){
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("]\n");
    printf("digite um numero para encontrar: ");
    scanf_s("%d", &num);

    printf("o valor foi encontrado na posicao: %d", busca_seq_rec(arr, ARRAY_SIZE, 0, num));
}