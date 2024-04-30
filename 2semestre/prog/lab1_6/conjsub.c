#include <stdio.h>

void subtracao(int a[], int n, int b[], int m){
   printf("[");
    for (int i = 0; i < n; i++){
        int exist = 0;
        for (int j = 0; j < m; j++){
            if (a[i] == b[j]){
                exist = 1;
                break;
            }
        }
        if (!exist){
            printf(" %d ", a[i]);
        }
    }
    printf("]\n");
}

int main(){
    int a[] = {0, 1, 3, 4, 2, 5, 6};
    int b[] = {0, 2, 1, 4};
    subtracao(a, sizeof(a)/sizeof((*a)), b, sizeof(b)/sizeof((*b)));
    return 0;
}