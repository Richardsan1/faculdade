#include <stdio.h>

int converter_bin(int n){
    // convert a bin num with 8 bits to decimal with recursion
    if (n < 10){
        return n;
    }

    return converter_bin(n/10) * 2 + n%10;

}

int main(){
    int bin;
    printf("Digite o valor binario: ");
    scanf_s("%d", &bin);

    printf("%d\n", converter_bin(bin));
    return 0;
}