#include <stdio.h>

int mul(int a, int b){
    if (a > b){
        if (b == 1){
            return a;
        }
        return a + mul(a, b-1);
    }
    if (a == 1){
        return b;
    }
    return b + mul(a-1, b);

}
int main(){
    int a, b;
    printf("digite um numero:");
    scanf("%d", &a);
    printf("digite um numero:");
    scanf("%d", &b);

    printf("%d", mul(a, b));
    return 0;
}