// que substituirá sua execução por meio da função execlp() para executar o comando ls no diretório
// atual.
// Requisitos:
//  O processo filho deve chamar execlp() para executar o comando ls (ou outro comando
// simples, como date).
//  Caso execlp() falhe, trate o erro (por exemplo, usando perror()).
//  O processo pai deverá usar wait() para aguardar o término da execução do filho e, em seguida,
// imprimir: “Comando executado com sucesso.”

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
       execlp("ls", "ls", "-a", NULL);
       perror("Erro ao executar o comando ls\n");
    } else {
        wait(NULL);
        printf("Comando executado com sucesso.\n");
    }
    return 0;
}