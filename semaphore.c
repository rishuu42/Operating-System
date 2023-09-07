#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t mutex;

void LockOpe() {
    sem_wait(&mutex);
    printf("Lock acquired by Child Process %d\n", getpid());
    sem_post(&mutex);
    printf("Lock released by Child Process %d\n", getpid());
}
int main() {
    LockOpe();
    if (sem_init(&mutex, 0, 1) != 0) {
        printf("Semaphore Failed");
        exit(1);
    }
    int num;
    printf("Enter number of Children Processes: ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        pid_t id = fork();
        LockOpe();
        if (id == -1) {
            printf("Fork failed");
            exit(1);
        } else if (id == 0) {
            LockOpe();
            exit(0);
        }
    }
    for (int i = 0; i < num; i++) {
        wait(NULL);
    }
    sem_destroy(&mutex);
return 0;
}
