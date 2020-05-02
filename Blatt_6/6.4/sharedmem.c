#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXCOUNT 100000000
#define NUM_CHILDREN 4
#define SHMSEGSIZE sizeof(int)

int main()
{
    int i, shmID, *shared_mem, count = 0;
    int pid[NUM_CHILDREN];

    //shared memory identifier returned into shmID
    shmID = shmget(IPC_PRIVATE, SHMSEGSIZE, IPC_CREAT | 0644);

    //shmat returnes memory adress associated to the shmID to our pointer variable
    shared_mem = (int*)shmat(shmID, 0, 0);
    *shared_mem = 0;

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid[i] = fork();

        if (pid[i] == -1) {
            printf("Forking child %i not possible!\n", i);
            return EXIT_FAILURE;
        }
        if (pid[i] == 0) {

            //all children are accessing shared memory at the same time, a lot of actions get lost
            while (*shared_mem < MAXCOUNT) {
                *shared_mem += 1;
                count++;
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

    //important to unmap shared memory segment from program with shmdt
    shmdt(shared_mem);
    //shmctl performs control operations on shared memory segment, IPC_RMID removes segment and destroys data associated with it
    shmctl(shmID, IPC_RMID, 0);
    return EXIT_SUCCESS;
}