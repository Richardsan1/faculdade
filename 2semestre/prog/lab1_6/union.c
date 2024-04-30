#include <stdio.h>
#include <stdlib.h>

void uniao(int a[], int n, int b[], int m){
    int * arr = malloc(sizeof(int)* (n+m));
    int size = 0;
    
    printf("[");
    for (int i = 0; i < n; i++){
        int exist = 0;
        for (int j = 0; j < size; j++){
            if (a[i] == arr[j]){
                exist = 1;
                break;
            }
        }
        if (!exist){
            arr[size] = a[i];
            size++;
            printf(" %d ", a[i]);
        }
    }
    for (int i = 0; i < m; i++){
        int exist = 0;
        for (int j = 0; j < size; j++){
            if (b[i] == arr[j]){
                exist = 1;
                break;
            }
        }
        if (!exist){
            arr[size] = b[i];
            size++;
            printf(" %d ", a[i]);
        }
    }
    printf("]\n");
    free(arr);
}

int main(){
    int a[] = {0, 1, 3, 4, 2, 5, 6};
    int b[] = {0, 2, 1, 4};
    uniao(a, sizeof(a)/sizeof((*a)), b, sizeof(b)/sizeof((*b)));
    return 0;
}