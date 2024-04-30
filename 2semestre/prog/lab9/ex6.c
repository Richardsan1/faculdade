#include <stdio.h>

int busca_bin_rec(int arr[], int num, int min, int max){
    int mid = (max+min)/2;
    
    if (arr[mid] == num){
        return mid;
    }
    if (max <= min){
        return -1;
    }
    if (arr[mid] > num){
        return busca_bin_rec(arr, num, min, mid-1);
    }
    if (arr[mid] < num){
        return busca_bin_rec(arr, num, mid+1, max);
    }
    return -1;
}

int main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int num;
    
    printf("escolha um numero para ser buscado: ");
    scanf_s("%d", &num);

    printf("posicao do numero: %d", busca_bin_rec(arr, num, 0, 10));
}