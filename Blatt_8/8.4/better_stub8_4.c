/**
 * UE Betriebssysteme
 *
 * Description:
 *   Threads - Performance
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    Better: split the critical area into two steps, first copy data from struct to local space,
            then calculate local sum and afterwards add to overall sum
            
    Time:   real    0m5.011s
            user    0m0.002s
            sys     0m0.003s

    */

    int thread_local_sum = 0;

    pthread_mutex_lock(&mutex);
    ThreadData* dat = (ThreadData*)thread_data;
    int loop_count = dat->n_records / THREADS;

    //array for copying data to local scope and afterwards sum it up
    int thread_local_data[loop_count];
    memcpy(&thread_local_data, dat->data + dat->offset, sizeof(int) * loop_count); //copying data from struct to local space
    pthread_mutex_unlock(&mutex);

    //make calculation
    for (int i = 0; i < loop_count; i++) {
        thread_local_sum += calc(thread_local_data, i);
    }

    //last step: add local sum to overall sum under mutex lock
    pthread_mutex_lock(&mutex);
    sum += thread_local_sum;
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