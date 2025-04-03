#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char buf[128];
    
    int fd_origem = open("lab2_ex3_origem.txt", O_RDONLY);
    if (fd_origem == -1) {
        printf("Erro ao abrir o arquivo de origem\n");
        return 1;
    }

    int fd_destino = open("lab2_ex3_destino.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_destino == -1) {
        printf("Erro ao abrir o arquivo de destino\n");
        close(fd_origem);
        return 1;
    }

    int n;
    while ((n = read(fd_origem, buf, sizeof(buf))) > 0) {
        if (write(fd_destino, buf, n) != n) {
            printf("erro ao escrever no arquivo de destino\n");
            close(fd_origem);
            close(fd_destino);
            return 1;
        }
    }

    if (n == -1) {
        printf("Erro ao ler o arquivo de origem\n");
    }

    close(fd_origem);
    close(fd_destino);
    return 0;
}