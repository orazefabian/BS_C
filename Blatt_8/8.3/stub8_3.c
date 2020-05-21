/**
 * UE Betriebssysteme
 *
 * Description:
 *   Threads - Bingo
 */

#include "barrier.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define N 3
#define CARDSIZE 10
#define NUMBERS 50
#define NUM_THREADS (N + 2) // N+2 threads (players + showmaster + monitor)

<<<<<<< HEAD
// typedef struct pthread_barrier {
//     pthread_mutex_t mutex;
//     pthread_cond_t cond;
//     volatile uint32_t flag;
//     size_t count;
//     size_t num;
// } pthread_barrier_t;
//
// int pthread_barrier_init(pthread_barrier_t* bar, int attr, int num)
// {
//     int ret = 0;
//     if ((ret = pthread_mutex_init(&(bar->mutex), 0)))
//         return ret;
//     if ((ret = pthread_cond_init(&(bar->cond), 0)))
//         return ret;
//     bar->flag = 0;
//     bar->count = 0;
//     bar->num = num;
//     return 0;
// }
//
// int pthread_barrier_wait(pthread_barrier_t* bar)
// {
//     int ret = 0;
//     uint32_t flag = 0;
//
//     if ((ret = pthread_mutex_lock(&(bar->mutex))))
//         return ret;
//
//     flag = bar->flag;
//     bar->count++;
//
//     if (bar->count == bar->num) {
//         bar->count = 0;
//         bar->flag = 1 - bar->flag;
//         if ((ret = pthread_cond_broadcast(&(bar->cond))))
//             return ret;
//         if ((ret = pthread_mutex_unlock(&(bar->mutex))))
//             return ret;
//         return 1;
//     }
//
//     while (1) {
//         if (bar->flag == flag) {
//             ret = pthread_cond_wait(&(bar->cond), &(bar->mutex));
//             if (ret)
//                 return ret;
//         } else {
//             break;
//         }
//     }
//
//     if ((ret = pthread_mutex_unlock(&(bar->mutex))))
//         return ret;
//     return 0;
// }

=======
>>>>>>> ad4d37623cbf2cbe9a941b8b88da9672ecbdc945
pthread_t thread[NUM_THREADS];
pthread_barrier_t barrier;
pthread_mutex_t mutex;
pthread_cond_t next;
int cards[N][CARDSIZE];
int masterNumber = 0; //number to check if showmaster has to draw new number
int numbersDrawn[NUMBERS];

int checkForNumber()
{
    int r;
    do {
        r = rand() % 50;
    } while (numbersDrawn[r] == 0);
    int draw = numbersDrawn[r];
    numbersDrawn[r] = 0;
    return draw;
}
// player thread
void* player(void* id)
{
    // TODO
    int* playerID = (int*)id;
    printf("Player %d started\n", *playerID);

    //initialize cards for player
    int r;
    for (int i = 0; i < CARDSIZE; i++) {
        r = (rand() % NUMBERS) + 1;
        cards[*playerID][i] = r;
    }

    int checks = 0; //amount of right numbers
    while (1) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        int num = masterNumber;
        pthread_mutex_unlock(&mutex);

        if (num == 0) {
            continue;
        }

        //check for right numbers
        for (int i = 0; i < CARDSIZE; i++) {
            if (cards[*playerID][i] == num) {
                cards[*playerID][i] = 0; //override with 0
                checks++;
            }

            //check for win
            if (checks == CARDSIZE) {

                printf("Player %d has won!\n", *playerID);
                for (int i = 0; i < NUM_THREADS; i++) {
                    pthread_cancel(thread[i]);
                }
                exit(0);
            }
        }

        pthread_barrier_wait(&barrier);
    }
}

// showmaster thread
void* showmaster(void* id)
{
    for (int i = 0; i < NUMBERS; i++) {
        numbersDrawn[i] = i + 1;
    }

    // TODO
    while (1) {
        pthread_mutex_lock(&mutex);

        while (masterNumber != 0) {
            pthread_cond_wait(&next, &mutex);
        }

        masterNumber = checkForNumber();

        pthread_mutex_unlock(&mutex);

        printf("Showmaster has drawn: %d\n", masterNumber);
    }
}

// monitor thread
void* monitor(void* id)
{

    // TODO
    while (1) {
        pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);

        for (int i = 0; i < N; i++) {
            printf("Player %d\n", i);
            for (int j = 0; j < CARDSIZE; j++) {
                printf("%d\t", cards[i][j]);
            }
            printf("\n");
        }
        sleep(1);
        masterNumber = 0; //indicate that master can draw

        pthread_cond_broadcast(&next);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[])
{
    // seed random number generator
    srand(time(NULL));

    // init barriers
    // TODO
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&next, NULL);
    pthread_barrier_init(&barrier, 0, N + 1); //player threads + monitor thread

    // create threads
    int i;
    int* thread_id = (int*)malloc(sizeof(int) * NUM_THREADS);

    // players (id:0 to N-1)
    for (i = 0; i < N; i++) {
        thread_id[i] = i;
        pthread_create(&thread[i], NULL, player, (void*)&thread_id[i]);
    }

    // showmaster (id:N)
    thread_id[N] = N;
    pthread_create(&thread[N], NULL, showmaster, (void*)&thread_id[N]);

    // monitor (id:N+1)
    thread_id[N + 1] = N + 1;
    pthread_create(&thread[N + 1], NULL, monitor, (void*)&thread_id[N + 1]);

    // wait for threads to join
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    free(thread_id);

    return EXIT_SUCCESS;
}
