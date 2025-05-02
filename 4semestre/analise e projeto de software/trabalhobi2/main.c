#include <stdio.h>
#include <stdlib.h>
#include "./boot.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Erro: sem arquivo de entrada\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo\n");
        return 1;
    }

    Mapa * mapas = boot(file);
    fclose(file);

    if (mapas == NULL) {
        fprintf(stderr, "Erro: não foi possível carregar os mapas\n");
        return 1;
    }

    return 0;
}