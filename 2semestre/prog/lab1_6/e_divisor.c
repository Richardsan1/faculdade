#include <stdio.h>

int divide(int divisor, int dividendo){
    if (dividendo % divisor == 0) {
        return 1;
    }
    return 0;
}
int divisores(int val) {
    int div =0;
    int i = 1;
    while(i <= val){
        if (divide(i, val)){
            div++;
        }
        i++;
    }
    return div;
}

int main(){
    int val;
    
    printf("Digite o dividendo: ");
    scanf("%d", &val);

    printf("quantidade de divisores: %d\n", divisores(val));
    
    return 0;
}