#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "strCartela.h"
#include "cartela.h"
#include "table.h"

int CARTEL_NUMBERS[50] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
int CARTEL_SIZE = 50;

void chooseNumber(int * alreadyChoose, int *size){
    int r = rand() % CARTEL_SIZE;
    alreadyChoose[*size] = CARTEL_NUMBERS[r];
    (*size)++;

    for (int i = r; i < CARTEL_SIZE - 1; i++) {
        CARTEL_NUMBERS[i] = CARTEL_NUMBERS[i + 1];
    }
    CARTEL_SIZE--;
}

int main() {
    char** cartelas = chooseCartelas();
    struct Cartela arr[4];
    int player = 0;
    
    for (int i = 0; i < 4; i++) {
        arr[i].numeros = split(cartelas[i]);
        arr[i].escolhidos = malloc(5 * sizeof(int));
        arr[i].hits = 0;
        for (int j = 0; j < 5; j++) {
            arr[i].escolhidos[j] = 0;
        }
    }

    int selectedNums[50];
    int size = 0;
    
    game:
    while (1){
        table(player, arr);
        printf("# SELECIONE UMA CARTELA ");
        switch (player)
        {
        case 0:
            printf("(2, 3 ou 4)");
            break;
        case 1:
            printf("(1, 3 ou 4)");
            break;
        case 2:
            printf("(1, 2 ou 4)");
            break;
        case 3:
            printf("(1, 2 ou 3)");
            break;
        }
        printf(" ou PRESSIONE ENTER PARA SORTEAR: ");

        char buff[4];
        fgets(buff, 4, stdin);

        if (buff[0] != '\n'){
            if (atoi(buff) < 1 || atoi(buff) > 4) {
                system("cls");
                printf("Cartela invalida!\n");
                goto game;
            }
            player = atoi(buff)-1;
        }
        
        system("cls");
        chooseNumber(selectedNums, &size);
        printf("############################################\n");
        printf("             NUMERO SORTEADO: %d\n", selectedNums[size-1]);
        printf("############################################\n");
        
        int win = verify(selectedNums[size-1], arr);
        if (win != -1){
            for (int i = 0; i < 4; i++){
                free(arr[i].numeros);
            }

            table(player, arr);
            if (win == player){
                printf("# PARABÉNS! VOCÊ VENCEU!!!\n");
                printf("# Entre o seu nome para constar no rol de vencedores: ");
                
                char name[50];
                scanf_s("%s", name, 50);
                
                FILE *file;
                fopen_s(&file, "vencedores.txt", "a");
                fprintf(file, "%s | ", name);
                time_t t = time(NULL);
                struct tm tm;
                localtime_s(&tm, &t);


                fprintf(file, "%02d-%02d-%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                fclose(file);
                
                break;
            }
            printf("# OUTRA CARTELA FOI COMPLETADA!\n");
            printf("# Melhor sorte na próxima vez!\n");
            break;
        }
    }

    return 0;
}