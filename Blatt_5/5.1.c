#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{

    pid_t pid1, pid2;

    for (int i = 0; i < 2; i++) {
        pid1 = fork();
        if (pid1 == 0) {
            printf("Outer Hello World (PID: %d, Parent: %d, PID Variable: %d)\n", getpid(), getppid(), pid1);
            for (int j = 0; j < 2; j++) {
                pid2 = fork();
                printf("-- Inner Hello World (PID: %d, Parent: %d, PID Variable: %d)\n", getpid(), getppid(), pid2);
                if (pid2 == 0) {
                    sleep(10000);
                    exit(0);
                }
            }
        }
    }
    sleep(10000);
    return 0;
}
