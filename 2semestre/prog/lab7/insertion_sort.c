#include <stdio.h>
#include <stdbool.h>
#include "vetor_utils.h"

void insertion_sort(int v[], int n) {
    int i;
    // para cada posição do vetor (1o percurso)
    for (i = 1; i < n; i++) {
      // guardar elemento
      int elemento = v[i];
      int j = i - 1;
      bool encontrou = false;
      // percorrer no sentido inverso enquanto não chegar ao início do vetor e não encontrar um menor
      while (j >= 0 && !encontrou) {
        // se o elemento do 2o. percurso for maior
        if (v[j] > elemento) {
          // deslocar elemento do 2o. percurso para a direita
          v[j+1] = v[j];
          // continuar procurando
          j--;
        }
        // se o elemento do 2o. percurso for menor encontramos a posição
        else encontrou = true;
      }
      // inserir elemento na posição encontrada
      v[j+1] = elemento;
    }
}

int main(void) {
  int n = 12;  // tente trocar o valor de n...
  int v[n];
  gerar_numeros(v, n);
  imprimir(v, n);
  insertion_sort(v, n);
  imprimir(v, n);
}