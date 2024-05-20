#include <stdio.h>

void troca(int *i, int *j){
    // Está errado por que da maneira que esta sendo passado, 
    // na troca de *j = *temp, *j vai receber *j, porque *i recebeu *j
    // o correto seria tratar temp como inteiro e não ponteiro
    int temp = *i;
    *i = *j;
    *j = temp;
}