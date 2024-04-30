// Desenvolva um programa para converter um valor de temperatura na escala Celsius para o
// equivalente na escala Fahrenheit.
// Seu programa deverá:
// • Solicitar o valor da temperatura na escala Celsius.
// • Converter para a escala Fahrenheit utilizando a fórmula:
// 𝐹 =
// 9
// 5
// ×𝐶 + 32
// • Imprimir o resultado na tela do computador utilizando uma mensagem no formato:
// Uma temperatura de ____ graus Celsius equivale a ____ graus Fahrenheit.
#include <stdio.h>

int main(){
    float cels;
    
    printf("digite a temperatura em celsius: ");
    scanf("%f", &cels);

    float fa = (1.8 * cels) + 32;

    printf("Uma temperatura de %.2f graus Celsius equivale a %.2f graus Fahrenheit.\n", cels, fa);

    return 0;
}