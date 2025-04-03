// EXERCÍCIO 5. Crie um programa em C que construa uma cadeia de três processos em sequência: o
// processo A (pai) cria um processo B; e o processo B, por sua vez, cria um processo C.
// Requisitos:
//  Cada processo deve imprimir uma mensagem do tipo “Eu sou o processo [PID] e meu pai é [PID
// do pai].”
//  Use wait() para assegurar que:
//  O processo B espere pela finalização do processo C antes de imprimir sua mensagem
// final.
//  O processo A espere que o processo B termine antes de exibir sua mensagem final.
//  Para melhor visualização, pode-se usar sleep() para criar um intervalo de 1 segundo entre as
// mensagens dos processos.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid == -1){
        printf("Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0){
        pid_t pid2 = fork();
        if(pid2 == -1){
            printf("Erro ao criar processo filho\n");
            return 1;
        } 
        wait(NULL);

        printf("Eu sou o processo %d e meu pai é %d. \n", getpid(), getppid());
        sleep(1);
        
    } else {
        wait(NULL);
        printf("Eu sou o processo %d e meu pai é %d. \n", getpid(), getppid());
    }
    return 0;
}