/**
 * PR Betriebssysteme -- matrix multiplication
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 5000


void* calc(void* param);

unsigned a[N][N];

int main() {
    pthread_t matrix_threads[N];
    unsigned  matrix_params[N];
    pthread_t threadID;
    srand(time(NULL));

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            a[i][j] = rand() % 10;
        }
    }

    for (size_t i = 0; i < N; i++) {
        matrix_params[i] = i;

        if (pthread_create(&threadID, NULL, calc, &matrix_params[i])) {
            perror("Error creating thread\n");
            exit(EXIT_FAILURE);
        }

        matrix_threads[i] = threadID;
    }

    for (size_t i = 0; i < N; i++) {
        threadID = matrix_threads[i];

        if (pthread_join(threadID, NULL)) {
            perror("Error joining thread\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

void* calc(void* param) {
    unsigned column     = *((unsigned*) param);
    unsigned column_sum = 0;

    for (size_t i = 0; i < N; i++) {
        column_sum += a[i][column];
    }

    printf("sum of column %u = %u\n", column, column_sum);

    pthread_exit(NULL);
}
