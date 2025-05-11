#include <stdio.h>
#include <stdlib.h>
#include "./boot.c"
#include "./runMap.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Erro: sem arquivo de entrada ou saida\n");
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
    
    FILE *out = fopen(argv[2], "w");
    for (int i = 0; i < 4; i++) {
        int size = 0;
        Item * escolha = runMap(&mapas[i], &size);
        float lucro = 0.0;

        fprintf(out, "--- FASE: %s ---\n", mapas[i].nome);
        fprintf(out, "Capacidade da mochila: %.2f\n", mapas[i].capacidade);
        fprintf(out, "Regra aplicada: %s\n\n", mapas[i].regra);
        for (int j = 0; j < size; j++) {
            lucro += escolha[j].valor;
            if (escolha[j].fracionado) {
                // Pegou (<inteiro/fracionario>) <nome do item> (<peso> kg, R$ <valor do item>)
                fprintf(out, "Pegou (fracionado) %s (%.2f kg, R$%.2f)\n", escolha[j].nome, escolha[j].peso, escolha[j].valor);
            } else {
                fprintf(out, "Pegou (inteiro) %s (%.2f kg, R$%.2f)\n", escolha[j].nome, escolha[j].peso, escolha[j].valor);
            }
        }
        fprintf(out, "Lucro da fase: R$%.2f\n\n", lucro);
    }


    return 0;
}