#include <stdio.h>

float fahrenheit_to_celsius(float fah){
    return (fah - 32) * 5/9;
}

float celsius_to_fahrenheit(float cel){
    return (1.8 * cel) + 32;
}

int main(){
    printf("Escolha a conversao a ser feita:\n");
    printf("(1) Converter de Celsius para Fahrenheit\n(2) Converter de Fahrenheit para Celsius\nOpcao:");
    float opt, temp;
    scanf("%f", &opt);

    if(opt == 1) {
        printf("Digite a temperatura: ");
        scanf("%.2f", &temp);
        printf("%.2f\n", celsius_to_fahrenheit(temp));
    } else if (opt == 2) {
        printf("Digite a temperatura: ");
        scanf("%.2f", &temp);
        printf("%.2f\n", fahrenheit_to_celsius(temp));
    } else {
        printf("Opcao invalida!\n");
    }

    return 0;
}