// Desenvolva um programa para calcular a hipotenusa de um triângulo retângulo.
// Seu programa deverá:
// • Solicitar os valores dos dois catetos do triângulo retângulo.
// • Calcular o cateto utilizando a fórmula:
// ℎ𝑖𝑝𝑜𝑡𝑒𝑛𝑢𝑠𝑎 = 𝑐𝑎𝑡𝑒𝑡𝑜1* + 𝑐𝑎𝑡𝑒𝑡𝑜2*
// • Imprimir o resultado na tela do computador utilizando uma mensagem no formato:
// Um triângulo retângulo com lados ___ e ___ tem uma hipotenusa igual a ____.

#include <stdio.h>
#include <math.h>

int main(){
    float ct1, ct2;

    printf("digite a porra do cateto: ");
    scanf("%f", &ct1);
    printf("digite a porra do cateto: ");
    scanf("%f", &ct2);

    float hipot = sqrt(pow(ct1, 2) + pow(ct2, 2));

    printf("Um triângulo retângulo com lados %.2f e %.2f tem uma hipotenusa igual a %.2f.\n", ct1, ct2, hipot);

    return 0;
}