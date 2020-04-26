#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/* define preprocessor macros */
#define READ 0
#define WRITE 1

int main(int argc, char** argv)
{
    /* ---------------------------- */
    /* step 1: create pipe          */
    int thePipe[2];
    pid_t pid;
    int buffer;
    srand(time(NULL));
    /* TODO pipe() and check whether is was successful */
    if (pipe(thePipe) == -1) {
        printf("Pipe creation failed\n");
    }
    /* ----------------------------- */
    /* step 2: fork stuff & co       */
    pid = fork();
    if (pid < (pid_t)0) {
        /* step 4.1: fork failed */
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }

    if (pid == (pid_t)0) {
        /* step 3: code for child */
        /* TODO close unnecessary pipes and create local variables */
        close(thePipe[READ]);
        /* TODO Generate random values */
        /* TODO write int values */
        /*      use sleep(rand() % 5) for better readability on display */
        for (int i = 0; i < 1 + (rand() % 10); i++) {
            buffer = rand() % 100;
            write(thePipe[WRITE], &buffer, sizeof(buffer));
            fprintf(stdout, "child writes: %i\n", buffer);
            sleep(rand() % 5);
        }
        /* TODO close pipes and exit */
        close(thePipe[WRITE]);
        exit(EXIT_SUCCESS);
    }
    if (pid > (pid_t)0) {
        /* step 4: code for parent */
        int min = __INT32_MAX__, max = 0, count = 0;
        float sum = 0, avg = 0;
        /* TODO close unnecessary pipes */
        close(thePipe[WRITE]);
        /* TODO Read int values from child */
        while ((read(thePipe[READ], &buffer, sizeof(buffer))) > 0) {
            if (min > buffer) {
                min = buffer;
            }
            if (max < buffer) {
                max = buffer;
            }
            count++;
            sum += buffer;
            avg = sum / count;
        }
        /* TODO calculate result and display the result on the screen */
        printf("min: %i, max: %i, sum: %f, avg: %f\n", min, max, sum, avg);
        /* TODO close pipes */
        close(thePipe[READ]);
        /* TODO wait for child and exit*/
        wait(0);
        exit(EXIT_SUCCESS);
    }
};
