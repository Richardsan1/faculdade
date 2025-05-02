#include <stdio.h>
#include <stdlib.h>
// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No *proximo;
} No;
// Função para criar um novo nó
No* criar_no(int valor) {
// Seu código aqui
    No *node = (No *)malloc(sizeof(No));
    if (node == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    node->valor = valor;
    node->proximo = NULL;
    return node;
}
// Função para inserir no início da lista
No* inserir_inicio (No *cabeca , int valor) {
// Seu código aqui
    No * node = criar_no(valor);
    node->proximo = cabeca;
    return node;
}
// Função para imprimir a lista
void imprimir_lista (No *cabeca) {
// Seu código aqui
    printf("[ ");
    while (cabeca != NULL){
        printf("%d ", cabeca->valor);
        cabeca = cabeca->proximo;
    }
    printf("]\n");
}
// Função para liberar a lista
void liberar_lista (No *cabeca) {
// Seu código aqui
    No *temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
    printf("Lista liberada\n");
}
int main () {
    No *lista = NULL; // Lista vazia
    // Inserir elementos
    lista = inserir_inicio (lista , 10);
    lista = inserir_inicio (lista , 20);
    lista = inserir_inicio (lista , 30);
    // Imprimir a lista
    printf("Lista: ");
    imprimir_lista (lista);
    // Liberar a memória
    liberar_lista (lista);
    return 0;
}