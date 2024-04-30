#include <stdio.h>

int resto(int a, int b){
    if (a > b){
        return resto(a-b, b);
    } 
    else if (b > a){
        return a;
    }
    return 0;    
}

int main(){
    int a, b;
    printf("Digite o dividendo: ");
    scanf_s("%d", &a);
    printf("Digite o divisor: ");
    scanf_s("%d", &b);

    printf("Resto: %d\n", resto(a,b));
    return 0;
}