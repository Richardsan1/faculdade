// Desenvolva um programa para calcular o IMC (Índice de Massa Corporal) de uma pessoa.
// Seu programa deverá:
// • Solicitar o peso da pessoa (em quilogramas).
// • Solicitar a altura da pessoa (em metros).
// • Calcular o IMC pela fórmula: 𝐼𝑀𝐶 = !"#$
// %&'()%!
// • Imprimir o resultado na tela do computador utilizando uma mensagem no formato:
// O IMC de uma pessoa com peso __ kg e altura __ m é igual a ___.
#include <stdio.h>

int main(){
    int mass;
    float height;

    printf("digite sua altura: ");
    scanf("%f", &height);
    printf("digite seu peso: ");
    scanf("%d", &mass);

    float imc = mass / (height* height);

    printf("O IMC de uma pessoa com peso %d kg e altura %.2f m é igual a %.2f.\n", mass, height, imc);

    return 0;
}