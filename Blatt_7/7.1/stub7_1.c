///
/// UE Betriebssysteme -- Fibonacci & shared memory
///
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXIMUM_SEQUENCE_NUMBER 10

typedef struct {
    unsigned last_valid_seq_no;
    unsigned long fibonacci_seq[MAXIMUM_SEQUENCE_NUMBER + 1];
} FibonacciSequence;

unsigned long fibo(unsigned n);

int main(int argc, char** argv)
{
    /* check argument */
    if (argc != 2) {
        printf("One argument required\n");
        exit(EXIT_FAILURE);
    }
    int num = atoi(argv[1]);
    if (num < 1 || num > 10) {
        printf("Arguments where not correct:\n");
        printf("Usage: ./main <n> // 0 < n < 11\n");
        exit(EXIT_FAILURE);
    }

    int shmID = 0;
    FibonacciSequence* shared_mem;
    pid_t pid;

    /* create shared mem and attach to local address space */
    // TODO

    shmID = shmget(IPC_PRIVATE, sizeof(FibonacciSequence), IPC_CREAT | 0644);
    shared_mem = (FibonacciSequence*)shmat(shmID, 0, 0);

    /* set sequence size */
    // TODO
    shared_mem->last_valid_seq_no = num;

    /* fork stuff */
    pid = fork();
    if (pid < (pid_t)0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    }
    if (pid == (pid_t)0) { // child
        for (int i = 0; i <= shared_mem->last_valid_seq_no; i++) {
            shared_mem->fibonacci_seq[i] = fibo(i);
        }

        /* detach shared mem from local address space */
        shmdt(shared_mem);
        exit(EXIT_SUCCESS);

    } else if (pid > (pid_t)0) { // parent
        waitpid(pid, NULL, 0);

        for (int i = 0; i < shared_mem->last_valid_seq_no; i++) {
            printf("fib %d\t= %ld\n", i + 1, shared_mem->fibonacci_seq[i]);
        }

        shmdt(shared_mem);

        shmctl(shmID, IPC_RMID, NULL);
    }

    return EXIT_SUCCESS;
}

/* Calculates the Fibonacci number of a given number n */
unsigned long fibo(unsigned n)
{
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibo(n - 1) + fibo(n - 2);
    }
}