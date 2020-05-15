/**
 * UE Betriebssysteme
 *
 * Description:
 *   Threads - Performance
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DATA 100
#define THREADS 5

typedef struct
{
    int* data;
    int  offset;
    int  n_records;
} ThreadData;

pthread_mutex_t mutex;
int             sum;

void* thread_function(void* thread_data);
int   calc(int* data, int index);
void  init(int* data);


int main(int argc, const char* argv[])
{
    srand(time(NULL));

    int* array = (int*) malloc(sizeof(int) * DATA);
    init(array);

    pthread_t threads[THREADS];

    pthread_mutex_init(&mutex, NULL);

    ThreadData* data = malloc(sizeof(ThreadData) * THREADS);

    sum = 0;

    printf("Starting ...\n");

    for (int i = 0; i < THREADS; i++)
    {
        data[i].data      = array;
        data[i].offset    = i * DATA / 5;
        data[i].n_records = DATA / 5;
        pthread_create(&threads[i], NULL, thread_function, (void*) data);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Done sum=%d\n", sum);

    free(array);
    free(data);

    return EXIT_SUCCESS;
}

void* thread_function(void* thread_data)
{
    ThreadData* dat = (ThreadData*) thread_data;

    // @TODO:   implement thread function
    //          iterate over dat->data, dat->n_records
    //          starting from dat->offset using function calc and
    //          add result to global variable sum

    pthread_exit(NULL);
}

int calc(int* data, int index)
{
    sleep(rand() % 3);
    return (data[index] + rand() % 100);
}

void init(int* data)
{
    for (int i = 0; i < DATA; i++)
    {
        data[i] = rand() % 100;
    }
}