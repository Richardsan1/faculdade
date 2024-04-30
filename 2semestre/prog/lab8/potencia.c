#include <stdio.h>

int potencia(int x, int n){
    if (n == 1){
        return x;
    }
    return x * potencia(x, n - 1);
}
int main(){
    int x, n;
    printf("digite o numero:");
    scanf("%d", &x);
    printf("digite a potencia:");
    scanf("%d", &n);

    printf("%d", potencia(x, n));
    return 0;
}