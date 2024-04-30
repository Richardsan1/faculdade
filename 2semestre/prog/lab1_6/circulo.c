// Desenvolva um programa para calcular a área de um círculo.
// Seu programa deverá:
// • Solicitar o raio do círculo.
// • Calcular a área do círculo utilizando a fórmula:
// r𝑎𝑖𝑜 = 𝜋𝑅*
// • Imprimir o resultado na tela do computador utilizando uma mensagem no formato:
// Um círculo com raio ____ tem área igual a _______.
#include <stdio.h>
#include <math.h>

int main(){
    int raio;

    printf("digite o raio do circulo: ");
    scanf("%d", &raio);

    float area = 3.14 * pow(raio, 2);

    printf("Um círculo com raio %d tem área igual a %.2f.\n", raio, area);

    return 0;
}