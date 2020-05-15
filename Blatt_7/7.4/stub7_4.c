/**
 * PR Betriebssysteme -- matrix multiplication
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define M 3
#define K 2
#define N 3

int a[M][K] = {
    { 1, 4 },
    { 2, 5 },
    { 3, 6 }
};
int b[K][N] = {
    { 1, 0, 0 },
    { 0, 1, 0 }
};
int c[M][N];

typedef struct
{
    int i; ///< row
    int j; ///< column
} ThreadParams;

void* calc(void* thread_dat)
{
    ThreadParams* dat = (ThreadParams*)thread_dat;
    // TODO implement thread function
    for (int n = 0; n < K; n++) {
        c[dat->i][dat->j] += a[dat->i][n] * b[n][dat->j];
    }
    // thread exit
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[M][N];
    //create mystruct for row and column data
    ThreadParams data[M][N];

    // TODO create MxN worker threads
    for (int i = 0; i < M; i++) //Rows
    {
        for (int j = 0; j < N; j++) //Columns
        {
            //save current row and column in data object
            data[i][j].i = i;
            data[i][j].j = j;

            pthread_create(&threads[i][j], NULL, calc, &data[i][j]);
        }
    }

    // TODO wait for threads ...
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            pthread_join(threads[i][j], NULL);

            // TODO print result
            printf("%d\t", c[i][j]); //print entry of result matrix
        }
        printf("\n"); //print new line
    }

    return EXIT_SUCCESS;
}
