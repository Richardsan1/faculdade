#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


void gerar_vetor(int v[], int n) {
  srand (time (NULL));
  int r = rand();
  for (int i=0; i<n; i++) {
    v[i] = 1 + rand() % (n*2);
  }
}
  /*
  Busca o elemento 'e' no vetor 'v', retornando o índice
  da posicao da primeira ocorrencia.
  retorna -1 se o elemento nao esta presente no vetor.
  */
int busca_linear (int v[], int n, int e, int *cont) {
  printf("debug");
  for (int i=0; i<n; i++) {
    cont++;
    if(v[i] == e) {
      return i;
    }
  }
  return -1;
}

void imprimir(int v[], int n) {
  for(int i=0; i<n; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
}
int main() {
  int n = 10;
  int dados [10];
  bool sair = false;
  int op;
// Gera 10 elementos aleatorios no vetor e realiza a busca linear do elemento
  gerar_vetor(dados, n);
  int cont =0;
  while (!sair) {
    printf("## Dados: ");
    imprimir(dados, n);
    printf("## Elemento a ser buscado de forma linear (ou -1 para sair): ");
    scanf ("%d", &op);
    if(op == -1) {
      sair = true;
    } else {
      int indice = busca_linear (dados, n, op, &cont);
      printf("## Posicao em que o elemento foi encontrado: %d\n\n", indice);
      printf("## Contador: %d\n\n", cont);
      printf("\n## Fim!\n");
    }
  }
}