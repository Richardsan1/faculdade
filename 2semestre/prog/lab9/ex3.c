#include <stdio.h>

int mdc(int a, int b){
    if (a > b){
        return mdc(a-b, b);
    } 
    else if (b > a){
        return mdc(a, b-a);
    }
    return a;    
}

int main(){
    int a, b;
    printf("Digite o numero A: ");
    scanf_s("%d", &a);
    printf("Digite o numero B: ");
    scanf_s("%d", &b);

    printf("MDC: %d\n", mdc(a,b));
    return 0;
}