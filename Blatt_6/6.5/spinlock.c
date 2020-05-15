#include "pthread_spinlock.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXCOUNT 1000000
#define NUM_CHILDREN 4
#define SHMSEGSIZE sizeof(int) + sizeof(pthread_spinlock_t)

int main()
{
    int i, shmID, *shared_mem, count = 0;
    int pid[NUM_CHILDREN];

    //shared memory identifier returned into shmID
    shmID = shmget(IPC_PRIVATE, SHMSEGSIZE, IPC_CREAT | 0644);

    //shmat returnes memory adress associated to the shmID to our pointer variable
    shared_mem = (int*)shmat(shmID, 0, 0);
    *shared_mem = 0;

    //create spinlock
    pthread_spinlock_t* spin = (pthread_spinlock_t*)(shared_mem + 1);

    pthread_spin_init(spin, PTHREAD_PROCESS_PRIVATE);

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid[i] = fork();

        if (pid[i] == -1) {
            printf("Forking child %i not possible!\n", i);
            return EXIT_FAILURE;
        }
        if (pid[i] == 0) {

            //all children are accessing shared memory at the same time, a lot of actions get lost
            while (*shared_mem < MAXCOUNT) {

                pthread_spin_lock(spin);
                if (*shared_mem != MAXCOUNT) {
                    *shared_mem += 1;
                    count++;
                }
                pthread_spin_unlock(spin);
            }
            printf("Child %i incremented value %i times!\n", i, count);
            shmdt(shared_mem);
            return EXIT_SUCCESS;
        }
    }
    for (i = 0; i < NUM_CHILDREN; i++) {
        waitpid(pid[i], NULL, 0);
    }
    printf("Shared Memory = %i \n", *shared_mem);

    pthread_spin_destroy(spin);

    //important to unmap shared memory segment from program with shmdt
    shmdt(shared_mem);
    //shmctl performs control operations on shared memory segment, IPC_RMID removes segment and destroys data associated with it
    shmctl(shmID, IPC_RMID, 0);
    return EXIT_SUCCESS;
}