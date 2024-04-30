#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define foreach(item, array, length) \
    for(int keep = 1, \
            count = 0;\
        keep && count != length; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)


int main(){
    int val, j = 0;
    printf("Digite o valor que deseja saber se e perfeito: ");
    scanf_s("%d", &val);
    int arr[MAX_SIZE];
    for (int i = 2; i <= val/2; i++){
        if (val % i == 0) {
            arr[j] = i;
            j++;
        }
    }
    int sum = 1 + val;
    foreach(int *v, arr, j){
        sum += *v;
    }
    if (sum == val*2){
        printf("%d e um numero perfeito\n", val);

    } else {
        printf("%d nao e um numero perfeito\n", val);
    }

    return 0;
} 