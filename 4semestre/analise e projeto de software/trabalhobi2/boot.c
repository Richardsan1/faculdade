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
    Item *itens;       // agora é ponteiro
    int qtdItens;      // quantidade real
    char *regra;
} Mapa;

void printItens(Item *itens, int qtdItens) {

    for (int i = 0; i < qtdItens; i++) {
        if (itens[i].nome == NULL) continue; // segurança para itens vazios

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

    // Passo 1: ler todas as linhas e armazenar temporariamente
    char *linhas[500];
    int numLinhas = 0;
    while (fgets(linha, sizeof(linha), file)) {
        linhas[numLinhas] = strdup(linha); // armazena cópia da linha
        numLinhas++;
    }

    // Passo 2: primeira passada — contar itens por mapa
    int itemCounts[4] = {0}; // máximo de 4 mapas

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

    // Passo 3: segunda passada — preencher dados
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
            mapas[mapaIndex].qtdItens = itemCounts[mapaIndex];
            mapas[mapaIndex].itens = malloc(sizeof(Item) * mapas[mapaIndex].qtdItens);
        } else if (strcmp(token, "CAPACIDADE") == 0) {
            mapas[mapaIndex].capacidade = atof(strtok(NULL, ":"));
        } else if (strcmp(token, "REGRA") == 0) {
            char *regra = strtok(NULL, ":");
            while (*regra == ' ') regra++; // remove espaços

            // remove espaços e '\r' finais
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
            while (*tipo == ' ') tipo++; // remove espaços
            item->tipo = strdup(tipo);

            item->fracionado = 0;
            itemIndex++;
        }

        free(linhas[i]); // libera memória da linha
    }

    return mapas;
}
