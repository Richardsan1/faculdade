#include <stdio.h>

void interseccao(int a[], int n, int b[], int m){
   printf("[");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i] == b[j]){
                printf(" %d ", a[i]);
                break;
            }
        }
    }
    printf("]\n");
}

int main(){
    int a[] = {0,1,4,2,5};
    int b[] = {0, 2, 1, 4};
    interseccao(a, sizeof(a)/sizeof((*a)), b, sizeof(b)/sizeof((*b)));
    return 0;
}