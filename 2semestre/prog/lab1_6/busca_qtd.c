#include <stdio.h>

int busca_qtde(int v[], int n, int e){
    int times = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == e) {
            times += 1;
        }
    }
    return times;
}