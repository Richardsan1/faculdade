#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAX_SIZE 10
int gerar_numeros(int * arr, int size){
    srand(time(NULL));
    int cont = 0;
    for (int i = 0; i < size; i++){
        int val = rand();
        int find = 1;
        for (int j = 0; j <= i; j++){
            cont++;
            if (val == arr[j]){
                find = 0;
                break;
            }
        }
        if (find){
            arr[i] = val;
        } else {
            i--;
        }
    }
    return cont;
}

int createArrCres(int * arr, int size){
    srand(time(NULL));
    int cont = 0;
    arr[0] = rand() % 1000;
    for (int i = 1; i < size; i++){
        arr[i] = (rand() % 1000) + arr[i-1];
        cont++;
    }
    return cont;
}

int createArrDecres(int * arr, int size){
    srand(time(NULL));
    int cont =0;
    arr[0] = rand() % 1000;
    for (int i = 1; i < size; i++){
        cont++;
        arr[i] = arr[i-1] - (rand() % 1000);
    }
    return cont;
}

void imprimir(int * arr, int size){
    printf("[ ");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf(" ]\n");
}

void trocar(int * arr, int a, int b){
    int c = arr[a];
    arr[a] = arr[b];
    arr[b] = c;
    
}

// int main(){
//     int arr1[MAX_SIZE]; 
//     int arr2[MAX_SIZE]; 
//     int arr3[MAX_SIZE];

//     int cont1 = createArr(arr1, MAX_SIZE);
//     int cont2 = createArrCres(arr2, MAX_SIZE);
//     int cont3 = createArrDecres(arr3, MAX_SIZE);

//     printArr(arr1, MAX_SIZE);
//     printf("cont: %d\n", cont1);
//     printArr(arr2, MAX_SIZE);
//     printf("cont: %d\n", cont2);
//     printArr(arr3, MAX_SIZE);
//     printf("cont: %d\n", cont3);
// }