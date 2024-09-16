#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10000

int mergeSteps = 0;
int insertSteps = 0;
// Função para mesclar duas sublistas
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
        mergeSteps++;
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
        mergeSteps++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        mergeSteps++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        mergeSteps++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        mergeSteps++;
    }
}

// Função recursiva para dividir e ordenar a lista
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Função para realizar o Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move os elementos do arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > key) {
            insertSteps++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    FILE *file;
    file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    int arr1[MAX_LEN];
    int arr2[MAX_LEN];
    int num, i = 0;

    while (fscanf(file, "%d", &num) != EOF && i < MAX_LEN) {
        arr1[i] = num;
        arr2[i] = num;
        i++;
    }
    fclose(file);

    int size = i; // Número de elementos lidos

    mergeSort(arr1, 0, size - 1);
    insertionSort(arr2, size);

    file = fopen("out1.txt", "w");
    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr1[i]);
    }
    fclose(file);

    file = fopen("out2.txt", "w");
    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr2[i]);
    }

    fclose(file);
    printf("Merge Sort: %d passos\n", mergeSteps);
    printf("Insertion Sort: %d passos\n", insertSteps);
    return 0;
}