#include <stdio.h>

void min_max(int v[], int lenght, int * min, int * max){
    for (int i =0; i < lenght; i++){
        if (v[i] > *max){
            *max = v[i];
        }
        if (v[i] < *min){
            *min = v[i];
        }
    }
}

int main(){
    int v[] = {2,1,3,4,5,6,7,8,9,10};
    int c = v[0], d = v[0];
    int *a = &c, *b = &d;
    min_max(v, sizeof(v)/sizeof(int), a, b);
    printf("minimo: %d\nmaximo: %d", c, d);
    return 0;
}