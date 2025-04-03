#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    char buf[128];
    int fd = open("lab2_ex1.txt", O_RDONLY);
    if(fd == -1){
        printf("Não foi possivel abrir o arquivo\n");
        exit(1);
    }
    read(fd, buf, 128);
    printf("%s\n", buf);
    close(fd);
    return 0;
}
