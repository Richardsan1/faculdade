// EXERCÍCIO 4. Desenvolva um programa em C que receba um número inteiro N (via argumentos de
//     linha de comando ou definido no código) e crie N processos filhos utilizando um loop.
//     Requisitos:
//      Cada processo filho deve imprimir sua ordem (por exemplo, “Eu sou o filho número X”) e seu
//     PID.
//      O processo pai deve aguardar o término de cada filho (utilizando wait() dentro do loop ou em
//     sequência).
//      Ao final, o pai deve imprimir: “Todos os processos filhos foram finalizados.”

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Número incorreto de argumentos. Use: %s <N>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    for(int i = 0; i< n; i++){
        pid_t pid = fork();
        if(pid == -1){
            printf("Erro ao criar processo filho\n");
            return 1;
        } else if (pid == 0){
            printf("Eu sou o filho número %d, meu PID é %d\n", i + 1, getpid());
            return 0;
        }
    }
    for(int i = 0; i < n; i++){
        wait(NULL); // Aguarda o término de cada processo filho
    }
    printf("Todos os processos filhos foram finalizados.\n");
    return 0;
}