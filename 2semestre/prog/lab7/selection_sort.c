#include <stdio.h>
#include <stdbool.h>
#include "vetor_utils.h"

void selection_sort(int v[], int n) {
    int i, j;
    // para cada posição do vetor (1º percurso)
    for (i = 0; i < n - 1; i++) {
        // inicializar o valor mínimo com o valor da posição atual
        int min = v[i];
        // percorrer cada uma das próximas posições do vetor (2º percurso)
        for (j = i + 1; j < n; j++) { 
            // se o elemento deste segundo percurso for menor que o mínimo
            if (v[j] < v[i]) { 
                // trocar os elementos entre as posições do 1º e 2º percursos
                trocar(v, i, j);
            }
        }
    }
}

int main(void) {
  int n = 10;  // tente trocar o valor de n...
  int v[n];
  gerar_numeros(v, n);
  imprimir(v, n);
  selection_sort(v, n);
  imprimir(v, n);
}