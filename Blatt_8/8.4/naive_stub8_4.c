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
    int offset;
    int n_records;
} ThreadData;

pthread_mutex_t mutex;
int sum;

void* thread_function(void* thread_data);
int calc(int* data, int index);
void init(int* data);

int main(int argc, const char* argv[])
{
    srand(time(NULL));

    int* array = (int*)malloc(sizeof(int) * DATA);
    init(array);

    pthread_t threads[THREADS];

    pthread_mutex_init(&mutex, NULL);

    ThreadData* data = malloc(sizeof(ThreadData) * THREADS);

    sum = 0;

    printf("Starting ...\n");

    for (int i = 0; i < THREADS; i++) {
        data[i].data = array;
        data[i].offset = i * DATA / 5;
        data[i].n_records = DATA / 5;
        pthread_create(&threads[i], NULL, thread_function, (void*)data);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Done sum=%d\n", sum);

    free(array);
    free(data);

    return EXIT_SUCCESS;
}

void* thread_function(void* thread_data)
{

    /*
    Naive: lock mutex at start of function and release it at the end
    
    Time:   real    0m27.459s
            user    0m0.002s
            sys     0m0.004s
    */
    pthread_mutex_lock(&mutex);

    ThreadData* dat = (ThreadData*)thread_data;
    int loop_count = dat->n_records / THREADS;
    for (int i = 0; i < loop_count; i++) {
        sum += calc(dat->data, i);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int calc(int* data, int index)
{
    sleep(rand() % 3);
    return (data[index] + rand() % 100);
}

void init(int* data)
{
    for (int i = 0; i < DATA; i++) {
        data[i] = rand() % 100;
    }
}