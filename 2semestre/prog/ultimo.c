#include <stdio.h>

int busca_ultimo(int v[], int n, int e) {
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] == e) {
            pos = i;
        }
    }
    return pos;
}