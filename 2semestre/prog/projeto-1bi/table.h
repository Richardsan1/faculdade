void table(int player, Cartela * cartelas){
    for (int i = 0; i < 4; i++){
        int win = 0;
        if (cartelas[i].hits == 5){
            win = 1;
        }
        char str[48]; 
        strcpy_s(str, sizeof str, win ? "*********  " : "           "); 
        for (int cont = 0; cont < 5; cont++){
            if (cartelas[i].escolhidos[cont] == 0) strcat_s(str, sizeof str, "     ");
            else win ? strcat_s(str, sizeof str, " ****") : strcat_s(str, sizeof str, " ----");
        }
        
        printf("%s\n", str);
        win ? printf("Cartela %d: * ", i+1) : printf("Cartela %d: | ", i+1);
        
        
        for (int j = 0; j < 5; j++){
            if (cartelas[i].numeros[j] < 10){
                printf(" ");
            }
            win ? printf("%d * ", cartelas[i].numeros[j]) :printf("%d | ", cartelas[i].numeros[j]);
        }
        
        if (i == player){
            printf("<<<<<<<<<<<<<<<<<<<<<");
        }

        printf("\n%s\n", str);
    }

}

int verify(int number, Cartela * cartelas){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 5; j++){
            if (cartelas[i].numeros[j] == number){
                cartelas[i].escolhidos[j] = 1;
                cartelas[i].hits++;
            }
        }
        if (cartelas[i].hits == 5){
            return i;
        }
    }
    return -1;
}