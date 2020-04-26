/**
 * UE Betriebssysteme
 *
 *   Fork demonstration; parent and child iterate over loop
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    /* ----------------------------- */
    /* step 0: check input arguments */
    /* TODO -- check for any input arguments, especially for -h and --help
     *         print usage information to dispay if required
     */
    int opt = 0;
    while ((opt = getopt(argc, argv, "h") != -1)) {
        switch (opt) {
        case 'h':
            printf("main -help\n");
            break;
        case '?': //unknown option
            printf("Option not known\n");
            return 1;
        default:
            return 0;
        }
    }
    /* ----------------------------- */
    /* step 1: some variables ...    */
    int N = 15;
    pid_t pid;
    /* ------------------------------ */
    /* step 3: do the work ...        */
    /* step 3.1: create new process via fork */
    /* TODO fork() */
    pid = fork();
    for (int i = 0; i < N; i++) {
        if (pid == 0) {
            //busy waiting
            int t = rand() % 3;
            time_t start = time(NULL);
            time_t now;
            do {
                now = time(NULL);
            } while (now - start < t);

            if (i % 2 == 0) {
                printf("--C--%d--%d\n", getpid(), i);
            }
            wait(0);

        } else if (pid > 0) {
            //sleep and wakeup
            int t = rand() % 3;
            sleep(t);

            if (i % 2 == 1) {
                printf("--P--%d--%d\n", getpid(), i);
            }
        } else {
            printf("fork failed!\n");
        }
    }

    return EXIT_SUCCESS;
};
