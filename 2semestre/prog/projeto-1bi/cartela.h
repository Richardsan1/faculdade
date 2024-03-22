char ** chooseCartelas() {
    FILE *file;
    int err = fopen_s(&file, "cartelas.txt", "r");

    if (err) {
        printf("Erro ao abrir o arquivo de cartelas\n");
        return NULL;
    }

    int i = 0;
    char *cartelas[40];
    char c[16];

    while (fgets(c, 16, file)) {
        cartelas[i] = malloc(strlen(c) + 1);
        strcpy_s(cartelas[i], strlen(c) + 1, c);
        i++;
    }
    
    fclose(file);
    srand(time(NULL));

    static char *chosen[4];
    for (int i =0; i < 4; i++) {
        int r =rand() % 40;
        // int r = i;
        chosen[i] = malloc(strlen(c) + 1);
        strcpy_s(chosen[i], strlen(cartelas[r])+1, cartelas[r]);
    }
    
    return chosen;
}

int * split(char * cart){
    int *arr = malloc(5 * sizeof(int));
    
    int j = 0;
    for (int i = 0; cart[i] != '\n' && cart[i] != '\0'; i++) {
        if (cart[i] == ',') {
            continue;
        }
        if (cart[i+1] != ',' && cart[i+1] != '\0' && cart[i+1] != '\n') {
            arr[j] = (cart[i] - '0') * 10 + (cart[i+1] - '0');
            i++;
        } else {
            arr[j] = cart[i] - '0';
        }
        j++;
    }
    
    return arr;
}