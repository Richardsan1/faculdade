#include <stdio.h>
void hm(int min, int*h,int*m){
    *h = min / 60;
    *m = min - (*h *60);
}

int main(){
    int a = 0, b = 0, *h= &a, *m = &b;
    hm(121, h, m);
    printf("%d horas e %d minutos", a, b);
    return 0;
}