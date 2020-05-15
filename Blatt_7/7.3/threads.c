#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void* count_down(void* counter);

int main(int argc, char const* argv[])
{
    //check for input arguments
    if (argc < 2) {
        printf("Arguments where not correct:\n");
        printf("Usage: ./main <n> // 0 < n\n");
        exit(EXIT_FAILURE);
    }
    int count = argc - 1;
    int num[count];

    if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            num[i - 1] = atoi(argv[i]);
        }
    }

    //create threads
    pthread_t threads[count];

    for (int i = 0; i < count; i++) {
        pthread_create(&threads[i], NULL, count_down, &num[i]);
    }

    //wait for threads to finish
    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* count_down(void* counter)
{
    pthread_t currId = pthread_self();
    int count = *((int*)counter);

    printf("Thread %d is counting from %d to 0\n", (int)currId, count);

    //for loop to simulate countdown
    for (int i = count; i >= 0; i--) {
        printf("Thread %d:\t %d\n", (int)currId, i);
        sleep(1);
    }

    printf("Thread %d has finished\n", (int)currId);
    pthread_exit(0);
}
