#include <stdio.h>

void imutavel(int x) { x += 10; }
void mutavel(int *x) { *x += 10; }

int main(){
    int a = 0;
    printf("a: %d\n", a);
    imutavel(a);
    // a continua 0 (foi passado por valor)
    printf("a: %d\n", a);
    int b = 0;
    printf("b: %d\n", b);
    mutavel(&b);
    // b retorna 10 (foi passado por referência)
    printf("b: %d\n", b);
}