Item * maximizeProfit(Mapa * mapa, void(* chooseFunc)(float, Mapa *, Item *, int *), int * size) {
    int n = mapa->qtdItens;
    float capacidadeRestante = mapa->capacidade;
    Item *itens = malloc(n * sizeof(Item));

    // Array para armazenar a relação valor/peso de cada item
    float valorPorPeso[n];
    for (int i = 0; i < n; i++) {
        if (mapa->itens[i].peso > 0) { // Evitar divisão por zero
            valorPorPeso[i] = mapa->itens[i].valor / mapa->itens[i].peso;
        } else {
            valorPorPeso[i] = 0;
        }
    }

    // Ordenar os itens com base na relação valor/peso (algoritmo guloso)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (valorPorPeso[i] < valorPorPeso[j]) {
                // Trocar os itens
                Item tempItem = mapa->itens[i];
                mapa->itens[i] = mapa->itens[j];
                mapa->itens[j] = tempItem;

                // Trocar a relação valor/peso
                float tempValorPorPeso = valorPorPeso[i];
                valorPorPeso[i] = valorPorPeso[j];
                valorPorPeso[j] = tempValorPorPeso;
            }
        }
    }

    // Selecionar os itens para maximizar o lucro de acordo com a regra
    chooseFunc(capacidadeRestante, mapa, itens, size);
    return itens;
}

void selectItems(float capacidadeRestante, Mapa * mapa, Item * itens, int * size) {
    int n = mapa->qtdItens;
    for (int i = 0; i < n; i++) {
        if (capacidadeRestante <= 0) {
            break; 
        }

        if (capacidadeRestante >= mapa->itens[i].peso) {
            itens[i] = mapa->itens[i];
            capacidadeRestante -= mapa->itens[i].peso;
            (*size)++;
        } else {
            itens[i] = mapa->itens[i];
            itens[i].peso = capacidadeRestante;
            itens[i].valor = (mapa->itens[i].valor / mapa->itens[i].peso) * capacidadeRestante;
            itens[i].fracionado = 1; 
            capacidadeRestante = 0; 
            (*size)++;
        }
    }
}

void selectItemsTec(float capacidadeRestante, Mapa * mapa, Item * itens, int * size) {
    int n = mapa->qtdItens;
    for (int i = 0; i < n; i++) {
        if (capacidadeRestante <= 0) {
            break; // Mochila cheia
        }

        if (capacidadeRestante >= mapa->itens[i].peso) {
            // Pega o item inteiro
            itens[i] = mapa->itens[i];
            capacidadeRestante -= mapa->itens[i].peso;
            (*size)++;
        } else {
            if (mapa->itens[i].tipo == "tecnologico") {
                continue; // Ignora itens tecnológicos
            }
            // Pega apenas uma fração do item
            itens[i] = mapa->itens[i];
            itens[i].peso = capacidadeRestante;
            itens[i].valor = (mapa->itens[i].valor / mapa->itens[i].peso) * capacidadeRestante;
            itens[i].fracionado = 1; // Indica que o item foi fracionado
            capacidadeRestante = 0; // Mochila cheia após pegar a fração
            (*size)++;
        }
    }
}

void selectThreeItems(float capacidadeRestante, Mapa * mapa, Item * itens, int * size) {
    int n = mapa->qtdItens;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (capacidadeRestante <= 0 || count >= 3) {
            break;
        }

        if (capacidadeRestante >= mapa->itens[i].peso) {
            itens[i] = mapa->itens[i];
            capacidadeRestante -= mapa->itens[i].peso;
            (*size)++;
            count++; 
        } else {
            itens[i] = mapa->itens[i];
            itens[i].peso = capacidadeRestante;
            itens[i].valor = (mapa->itens[i].valor / mapa->itens[i].peso) * capacidadeRestante;
            itens[i].fracionado = 1; 
            capacidadeRestante = 0; 
            (*size)++;
            count++; 
        }
    }
}

Item * runMap(Mapa * mapa, int * size) {
    Item * itensEscolhidos = NULL;
    char * regra = mapa->regra;
    if (strcmp(regra, "MAGICOS_VALOR_DOBRADO") == 0) {
        for (int i = 0; i <mapa->qtdItens; i++) {
            if (strcmp(mapa->itens[i].tipo, "magico") == 0) {
                mapa->itens[i].valor *= 2;
            }
        }
        itensEscolhidos = maximizeProfit(mapa, selectItems, size);
    } else if(strcmp(regra, "TECNOLOGICOS_INTEIROS") == 0){
        itensEscolhidos = maximizeProfit(mapa, selectItemsTec, size);
    } else if(strcmp(regra, "SOBREVIVENCIA_DESVALORIZADA") == 0){
        for (int i = 0; i <mapa->qtdItens; i++) {
            if (strcmp(mapa->itens[i].tipo, "tecnologico") == 0) {
                mapa->itens[i].valor *= 0.8;
            }
        }
        itensEscolhidos = maximizeProfit(mapa, selectItems, size);
    } else if(strcmp(regra, "TRES_MELHORES_VALOR_PESO") == 0){
        itensEscolhidos = maximizeProfit(mapa, selectThreeItems, size);
    } else {
        printf("Regra não reconhecida.\n");
    }
    return itensEscolhidos;
}