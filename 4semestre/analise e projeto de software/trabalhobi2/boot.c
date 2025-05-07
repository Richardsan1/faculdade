#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char *nome;
    float peso;
    float valor;
    char *tipo;
    int fracionado;
} Item;

typedef struct Mapa {
    char *nome;
    float capacidade;
    Item *itens;       
    int qtdItens;      
    char *regra;
} Mapa;

void printItens(Item *itens, int qtdItens) {

    for (int i = 0; i < qtdItens; i++) {
        if (itens[i].nome == NULL) continue; 

        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", itens[i].nome);
        printf("  Peso: %.2f\n", itens[i].peso);
        printf("  Valor: %.2f\n", itens[i].valor);
        printf("  Tipo: %s\n", itens[i].tipo);
        if (itens[i].fracionado) {
            printf("  [Item fracionado]\n");
        }
        printf("\n");
    }
}

Mapa *boot(FILE *file) {
    char linha[100];
    Mapa *mapas = malloc(sizeof(Mapa) * 4);
    int mapaIndex = -1;
    int itemIndex = 0;

    char *linhas[500];
    int numLinhas = 0;
    while (fgets(linha, sizeof(linha), file)) {
        linhas[numLinhas] = strdup(linha); 
        numLinhas++;
    }


    int itemCounts[4] = {0};

    int currentMap = -1;
    for (int i = 0; i < numLinhas; i++) {
        char *linhaTrim = strdup(linhas[i]);
        linhaTrim[strcspn(linhaTrim, "\n")] = '\0';

        if (strncmp(linhaTrim, "FASE", 4) == 0) {
            currentMap++;
        } else if (strncmp(linhaTrim, "ITEM", 4) == 0) {
            itemCounts[currentMap]++;
        }
        free(linhaTrim);
    }

    mapaIndex = -1;
    itemIndex = 0;
    for (int i = 0; i < numLinhas; i++) {
        char *linhaAtual = linhas[i];
        linhaAtual[strcspn(linhaAtual, "\n")] = '\0';

        char *token = strtok(linhaAtual, ":");
        if (strcmp(token, "FASE") == 0) {
            mapaIndex++;
            itemIndex = 0;

            mapas[mapaIndex].nome = strdup(strtok(NULL, ":"));
            mapas[mapaIndex].nome[strlen(mapas[mapaIndex].nome)-1] = '\0';
            mapas[mapaIndex].qtdItens = itemCounts[mapaIndex];
            mapas[mapaIndex].itens = malloc(sizeof(Item) * mapas[mapaIndex].qtdItens);
        } else if (strcmp(token, "CAPACIDADE") == 0) {
            mapas[mapaIndex].capacidade = atof(strtok(NULL, ":"));
        } else if (strcmp(token, "REGRA") == 0) {
            char *regra = strtok(NULL, ":");
            while (*regra == ' ') regra++; 

            char *end = regra + strlen(regra) - 1;
            while (end > regra && (*end == ' ' || *end == '\r')) {
                *end = '\0';
                end--;
            }

            mapas[mapaIndex].regra = strdup(regra);
        } else if (strcmp(token, "ITEM") == 0) {
            token = strtok(NULL, ":");

            Item *item = &mapas[mapaIndex].itens[itemIndex];
            char * nome =strdup(strtok(token, ","));
            while (*nome == ' ') nome++;
            item->nome = nome;
            item->peso = atof(strtok(NULL, ","));
            item->valor = atof(strtok(NULL, ","));

            char *tipo = strtok(NULL, ",");
            while (*tipo == ' ') tipo++; 
            item->tipo = strdup(tipo);

            item->fracionado = 0;
            itemIndex++;
        }

        free(linhas[i]);
    }

    return mapas;
}
