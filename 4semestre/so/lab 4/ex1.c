// EXERCÍCIO 1. Crie um programa em C que use a função fork() para criar um processo filho. Cada
// processo (pai e filho) deverá imprimir seu próprio PID.
// Requisitos:
//  O processo pai deve imprimir uma mensagem informando: “Eu sou o processo pai, meu PID é
// XXX e criei um filho com PID YYY.”
//  O processo filho deve imprimir: “Eu sou o processo filho, meu PID é YYY.”
//  Realize o tratamento de erros caso o fork() falhe.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if(pid == -1){
        printf("Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0){
        printf("Eu sou o processo filho, meu PID é %d\n", getpid());
    } else {
        printf("Eu sou o processo pai, meu PID é %d e criei um filho com PID %d\n", getpid(), pid);
    }
    return 0;
}