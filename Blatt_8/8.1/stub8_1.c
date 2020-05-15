/**
 * UE Betriebssysteme
 *
 * Description:
 *   Threads: Producer-Consumer
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// shared data structure
typedef struct
{
    int threadID;
    struct timeval time;
} ThreadData;

// mutex & cond vars
pthread_mutex_t mutex;
pthread_cond_t condFull;
pthread_cond_t condEmpty;

// shared var
ThreadData mem;

// status var filled (empty == 0, filled == 1)
int filled = 0;

// producer
void* producer(void* id)
{
    int* threadID = (int*)id;
    printf("Producer %i\n", *threadID);

    // TODO producer
    while (1) {

        //lock mutex
        pthread_mutex_lock(&mutex);

        while (filled) {
            //wait for empty condition
            pthread_cond_wait(&condEmpty, &mutex);
        }

        //write data to shared var ThreadData
        mem.threadID = *threadID;
        gettimeofday(&mem.time, NULL);
        sleep(1);

        printf("Producer %d writes \t--> ThreadID: %d \t--> Time: %ld\n", *threadID, mem.threadID, mem.time.tv_sec);

        filled = 1;

        //awake other thread and unlock mutex
        pthread_cond_signal(&condFull);
        pthread_mutex_unlock(&mutex);
    }

    /* thread exit */
    free(threadID);
    pthread_exit(NULL);
}

// consumer
void* consumer(void* id)
{
    int* threadID = (int*)id;
    printf("Consumer %i\n", *threadID);

    // TODO consumer

    while (1) {
        pthread_mutex_lock(&mutex);

        while (!filled) {
            pthread_cond_wait(&condFull, &mutex);
        }

        printf("Consumer %d reads \t--> ThreadID: %d \t--> Time: %ld\n", *threadID, mem.threadID, mem.time.tv_sec);
        filled = 0;

        pthread_cond_signal(&condEmpty);
        pthread_mutex_unlock(&mutex);
    }

    /* thread exit */
    free(threadID);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t thread[5]; //(3+2)5 threads
    int* thread_id;

    srand(time(NULL));

    // TODO init mutex & condition vars
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condFull, NULL);
    pthread_cond_init(&condEmpty, NULL);

    // create producer threads
    for (int i = 0; i < 3; i++) {
        thread_id = (int*)malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&thread[i], NULL, producer, (void*)thread_id);
    }
    // Create consumer threads
    for (int i = 0; i < 2; i++) {
        thread_id = (int*)malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&thread[3 + i], NULL, consumer, (void*)thread_id);
    }

    // wait for threads to join
    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condEmpty);
    pthread_cond_destroy(&condFull);

    return EXIT_SUCCESS;
}
