#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_PROCESSES 4
#define ARRAY_SIZE 10000000

typedef struct {
    int data[ARRAY_SIZE];
    int partial_max[NUM_PROCESSES];
} SharedData;

void find_max(int process_id, SharedData* shared_memory);

int main() {
    int shmid;
    SharedData* shared_memory;

    shmid = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shared_memory = (SharedData*) shmat(shmid, NULL, 0);
    if (shared_memory == (void*) -1) {
        perror("shmat");
        exit(1);
    }
    printf("Segmento de memória compartilhada (ID: %d) criado e anexado.\n", shmid);
    printf("Pai (PID: %d) populando o array com %d números aleatórios...\n", getpid(), ARRAY_SIZE);
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shared_memory->data[i] = rand();
    }
    printf("Array populado.\n");

    pid_t pid;
    printf("Pai esperando pelos %d filhos...\n", NUM_PROCESSES);
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int chunk_size = ARRAY_SIZE / NUM_PROCESSES;
        int start_index = i * chunk_size;
        int end_index = (i == NUM_PROCESSES - 1) ? ARRAY_SIZE : start_index + chunk_size;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            printf("Filho %d (PID: %d) procurando na faixa [%d, %d)\n", i, getpid(), start_index, end_index);
            find_max(i, shared_memory);
            exit(0);
        }
    }
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }
    printf("Todos os filhos terminaram.\n");

    int global_max = -1;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Filho %d encontrou o máximo parcial: %d\n", i, shared_memory->partial_max[i]);
        if (shared_memory->partial_max[i] > global_max) {
            global_max = shared_memory->partial_max[i];
        }
    }

    printf("\nO MÁXIMO GLOBAL ENCONTRADO É: %d\n", global_max);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segmento de memória compartilhada liberado.\n");

    
    return 0;
}

void find_max(int process_id, SharedData* shared_memory) {
    int chunk_size = ARRAY_SIZE / NUM_PROCESSES;
    int start_index = process_id * chunk_size;
    int end_index = start_index + chunk_size;

    if (process_id == NUM_PROCESSES - 1) {
        end_index = ARRAY_SIZE;
    }

    int local_max = -1;
    for (int i = start_index; i < end_index; i++) {
        if (shared_memory->data[i] > local_max) {
            local_max = shared_memory->data[i];
        }
    }
    
    shared_memory->partial_max[process_id] = local_max;
    
    shmdt(shared_memory);
}