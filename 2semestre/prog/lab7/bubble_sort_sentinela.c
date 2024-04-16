#include <stdio.h>
#include <stdbool.h>
#include "vetor_utils.h"

void bubble_sort_sentinela(int v[], int n) {
    int i, contador;
    // repetir (n – 1) vezes
    for (contador = 1; contador <= n-1; contador++) {
        bool sentinela = false;
        // percorrer o vetor
        for (i = 0; i < n-1; i++) {
            // se elemento atual for maior que o próximo
            if (v[i] > v[i+1]) {
                // troca os elementos entre as 2 posições
                trocar(v, i, i+1);
                sentinela = true;
            }
        }
        if (!sentinela) return;
    }
}

int main(void) {
  int n = 10;  // tente trocar o valor de n...
  int v[n];
  gerar_numeros(v, n);
  imprimir(v, n);
  bubble_sort_sentinela(v, n);
  imprimir(v, n);
}