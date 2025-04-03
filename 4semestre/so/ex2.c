#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    char buf[128];
    int fd = open("lab2_ex2.txt", O_RDONLY);
    if(fd == -1){
        printf("Não foi possivel abrir o arquivo\n");
        exit(1);
    }
    int lines = 0;
    int n;
    while((n = read(fd, buf, 128)) > 0){
        for(int i = 0; i < n; i++){
            if(buf[i] == '\n'){
                lines++;
            }
        }
    }
    printf("Número de linhas: %d\n", lines);
    close(fd);
    return 0;
}