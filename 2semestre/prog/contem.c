#include <stdio.h>
#include <stdbool.h>

bool contem(int v[], int n, int e){
    for (int i = 0; i < n; i++){
        if (v[i] == e){
            return true;
        }
    }
    return false;
}