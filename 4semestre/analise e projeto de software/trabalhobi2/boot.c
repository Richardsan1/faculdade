#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGICOS_VALOR_DOBRADO 1
#define TECNOLOGICOS_INTEIROS 2
#define SOBREVIVENCIA_DESVALORIZADA 3
#define TRES_MELHORES_VALOR_PESO 4

typedef struct Item{
    char * nome;
    float peso;
    float valor;
    char * tipo;
} Item;

typedef struct Mapa{
    char * nome;
    float capacidade;
    Item itens[50];
    char * regra;
} Mapa;

void printMapa(Mapa * mapas, int pos){
    printf("Nome: %s\n", mapas[pos].nome);
    printf("Regra: %s\n", mapas[pos].regra);
    printf("Capacidade: %.2f\n", mapas[pos].capacidade);
    for (int i = 0; i < sizeof(mapas[pos].itens) / sizeof(Item); i++){
        printf("Item %d: %s | ", i, mapas[pos].itens[i].nome);
        printf("Peso: %.2f | ", mapas[pos].itens[i].peso);
        printf("Valor: %.2f | ", mapas[pos].itens[i].valor);
        printf("Tipo: %s\n", mapas[pos].itens[i].tipo);
    }
}

Mapa * boot(FILE * file){
    char linha[100];
    Mapa * mapa = malloc(sizeof(Mapa)*4);
    int mapaIndex = -1;
    int itemIndex = 0;
    while(fgets(linha, sizeof(linha), file)){ 
        linha[strcspn(linha, "\n")] = '\0';       
        char * token = strtok(linha, ":");
        if (strcmp(token, "FASE") == 0) {
            mapaIndex++;
            itemIndex = 0;
            mapa[mapaIndex].nome = malloc(50 * sizeof(char));
            strcpy(mapa[mapaIndex].nome, strtok(NULL, ":"));
        } else if (strcmp(token, "CAPACIDADE") == 0) {
            mapa[mapaIndex].capacidade = atof(strtok(NULL, ":"));
        } else if (strcmp(token, "REGRA") == 0){
            mapa[mapaIndex].regra = malloc(50 * sizeof(char));
            strcpy(mapa[mapaIndex].regra, strtok(NULL, ":"));
        } else if (strcmp(token, "ITEM") == 0) {
            token = strtok(NULL, ":");
            mapa[mapaIndex].itens[itemIndex].nome = malloc(50 * sizeof(char));
            mapa[mapaIndex].itens[itemIndex].tipo = malloc(50 * sizeof(char));
            
            strcpy(mapa[mapaIndex].itens[itemIndex].nome, strtok(token, ","));
            mapa[mapaIndex].itens[itemIndex].peso = atof(strtok(NULL, ","));
            mapa[mapaIndex].itens[itemIndex].valor = atoi(strtok(NULL, ","));
            strcpy(mapa[mapaIndex].itens[itemIndex].tipo, strtok(NULL, ","));
            itemIndex++;
        }
    }
    // printMapa(mapa, 0);
    // printMapa(mapa, 1);
    return mapa;
}