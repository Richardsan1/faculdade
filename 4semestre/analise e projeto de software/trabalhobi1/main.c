#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função de backtracking para verificar se é possível distribuir os arquivos
int backtrack(int files[], int n, int index, int spaceA, int spaceB, int maxSpace, int pendriveA[], int *sizeA, int pendriveB[], int *sizeB) {
    if (index == n) {
        // Todos os arquivos foram processados
        return 1;
    }

    // Tentar colocar o arquivo atual no pendrive A
    if (spaceA + files[index] <= maxSpace) {
        pendriveA[*sizeA] = files[index];
        (*sizeA)++;
        if (backtrack(files, n, index + 1, spaceA + files[index], spaceB, maxSpace, pendriveA, sizeA, pendriveB, sizeB)) {
            return 1;
        }
        (*sizeA)--; // Backtrack
    }

    // Tentar colocar o arquivo atual no pendrive B
    if (spaceB + files[index] <= maxSpace) {
        pendriveB[*sizeB] = files[index];
        (*sizeB)++;
        if (backtrack(files, n, index + 1, spaceA, spaceB + files[index], maxSpace, pendriveA, sizeA, pendriveB, sizeB)) {
            return 1;
        }
        (*sizeB)--; // Backtrack
    }

    // Não foi possível distribuir o arquivo atual
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Combinação não realizada. Parâmetros incorretos.\n");
        printf("Utilizar comando:\n");
        printf("./backup <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA>\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Combinação não realizada. Arquivo de entrada não existe.\n");
        printf("Utilizar comando:\n");
        printf("./backup <ARQUIVO_ENTRADA> <ARQUIVO_SAÍDA>\n");
        return 1;
    }

    char line[128];
    fgets(line, 128, input);
    int tests = atoi(line);

    FILE *out = fopen(argv[2], "w");
    for (int i = 0; i < tests; i++) {
        fgets(line, 128, input);

        char *token;
        token = strtok(line, " ");
        int size = atoi(token);
        
        token = strtok(NULL, " ");
        int qtdFiles = atoi(token);

        int files[qtdFiles];
        for (int j = 0; j < qtdFiles; j++) {
            fgets(line, 128, input);
            files[j] = atoi(line);
        }

        int pendriveA[qtdFiles], pendriveB[qtdFiles];
        int sizeA = 0, sizeB = 0;

        // Usar backtracking para verificar se é possível distribuir os arquivos
        if (backtrack(files, qtdFiles, 0, 0, 0, size / 2, pendriveA, &sizeA, pendriveB, &sizeB)) {
            fprintf(out, "%d GB\n", size);
            fprintf(out, "\nPendrive A (%d GB)\n", size / 2);
            for (int j = 0; j < sizeA; j++) {
                fprintf(out, "%d GB\n", pendriveA[j]);
            }
            fprintf(out, "\nPendrive B (%d GB)\n", size / 2);
            for (int j = 0; j < sizeB; j++) {
                fprintf(out, "%d GB\n", pendriveB[j]);
            }
            fprintf(out, "\n");
        } else {
            fprintf(out, "%d GB\n", size);
            fprintf(out, "\nImpossível gravar todos os arquivos nos pendrives.\n");
        }
    }

    fclose(input);
    fclose(out);
    return 0;
}