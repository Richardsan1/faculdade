#include <stdio.h>

void tabuada(int val){
    for (int i = 1; i <=10; i++){
        printf("%d * %d = %d\n", val, i, val*i);
    }
}

int main(){
    for (int i = 1; i < 10; i++){
        tabuada(i);
    }
    return 0;    
}