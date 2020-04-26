/**
 * UE Betriebssysteme
 *
 *   Fork demonstration; command line intepreter using exec
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* command = argv[1];
    char* arguments[argc];

    int i;
    for (i = 1; i < argc; i++) {
        arguments[i - 1] = argv[i];
    }
    arguments[argc - 1] = NULL;

    pid_t pid;
    pid = fork();
    if (pid == 0) {
        //execvp to call shell functions
        return execvp(command, arguments);
    }
    if (pid > 0) {
        wait(0);
    }
    if (pid < 0) {
        printf("Fork failed\n");
    }
};
