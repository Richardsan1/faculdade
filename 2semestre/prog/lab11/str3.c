#include <stdio.h>
#include <string.h>
#define MAX_SIZE 50
int main(){
    char name[MAX_SIZE];
    printf("Digite o seu nome: ");
    scanf_s("%s", &name);

    for (int i = strlen(name)-1; i >= 0; i--){
        printf("%c", name[i]);
    }
    printf("\n");

    return 0;
}