#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FULLBASH "/bin/bash"
#define BASH "bash"
#define BASHOPTION "-c"

#define READ 0
#define WRITE 1

int main(int argc, char** argv)
{
    /* ----------------------------- */
    /* step 0: check input arguments */
    if (argc < 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("\nUSAGE: %s, \"<cmd1>\" \"<cmd2>\"\n\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* ----------------------------- */
    /* step 1: pipes                 */
    int thePipe[2]; /* pipe:  */

    // TODO
    if (pipe(thePipe) == -1) {
        perror("Pipe creation failed!");
        exit(EXIT_FAILURE);
    }

    /* ----------------------------- */
    /* step 2: fork stuff & co       */
    pid_t pid_c1, pid_c2;
    pid_c1 = fork();

    if (pid_c1 == (pid_t)0) {
        /* code for first child */
        char* command = argv[1];
        char* const arguments[] = { command, argv[2], NULL };
        close(thePipe[READ]);
        //redirect stdout to thepipe
        dup2(thePipe[WRITE], STDOUT_FILENO);
        execvp(command, arguments);
    }

    pid_c2 = fork();

    if (pid_c2 == (pid_t)0) {
        /* code for second child */
        char* command = argv[3];
        char* const arguments[] = { command, argv[4], NULL };
        close(thePipe[WRITE]);
        //redirect stdin to read end of thepipe
        dup2(thePipe[READ], STDIN_FILENO);
        execvp(command, arguments);
    }

    /* code for parent */
    waitpid(0, NULL, 0);
    close(thePipe[WRITE]);
    close(thePipe[READ]);

    return EXIT_SUCCESS;
}
