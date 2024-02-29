#include <stdio.h>
#include <stdlib.h>
#define foreach(item, array, length) \
    for(int keep = 1, \
            count = 0;\
        keep && count != length; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)


int main(){
    int val, j = 0;
    printf("Digite o valor que deseja saber os divisores: ");
    scanf_s("%d", &val);
    int arr[50];
    for (int i = 2; i <= val/2 + 1; i++){
        if (val % i == 0) {
            arr[j] = i;
            j++;
        }
    }
    printf("Os divisores de %d sao 1 ", val);
    
    foreach(int *v, arr, j){
        printf("%d ", *v);
    }
    
    printf("%d\n", val);

    return 0;
}