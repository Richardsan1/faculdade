#include <stdio.h>

int busca_primeiro(int v[], int n, int e) {
    for (int i = 0; i < n; i++) {
        if (v[i] == e) {
            return i;
        }
    }
    return -1;
}