// EXERCÍCIO 2. Utilizando o programa do Exercício 1, modifique-o para que o processo pai aguarde a
// conclusão do processo filho antes de finalizar. Após o término do filho, o pai deverá imprimir uma
// mensagem de confirmação.
// Requisitos:
//  O processo filho pode executar uma tarefa simples, como um loop com algumas mensagens e
// um intervalo em segundos.
//  O processo pai deverá usar wait() para esperar que o filho termine.
//  Após o wait(), imprima: “Processo filho finalizado.”

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
        for(int i = 0; i < 5; i++){
            printf("Processo filho executando...\n");
            sleep(1);
        }
    } else {
        wait(NULL);
        printf("Processo filho finalizado.\n");
    }
    return 0;
}