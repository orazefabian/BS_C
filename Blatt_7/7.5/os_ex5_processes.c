#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N 5000

void calc(unsigned column);

unsigned a[N][N];

int main()
{
    pid_t matrix_processes[N];
    unsigned column;

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            a[i][j] = rand() % 10;
        }
    }

    for (size_t i = 0; i < N; i++) {
        column = i;
        matrix_processes[i] = fork();

        if (matrix_processes[i] < (pid_t)0) {
            fprintf(stderr, "Fork failed.\n");
            exit(EXIT_FAILURE);
        }

        if (matrix_processes[i] == (pid_t)0) {
            /* child process */
            calc(column);

            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < N; i++) {
        waitpid(matrix_processes[i], NULL, 0);
    }
    exit(EXIT_SUCCESS);
}
void calc(unsigned column)
{
    unsigned column_sum = 0;

    for (size_t i = 0; i < N; i++) {
        column_sum += a[i][column];
    }

    printf("sum of column %u = %u\n", column, column_sum);
}
