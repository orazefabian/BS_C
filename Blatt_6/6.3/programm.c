#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

typedef struct IntCharPair {
    int val;
    char c;
} IntCharPair;

void init(IntCharPair* data)
{
    //annahme: init setzt struct auf initialwert c = a und den dazugehörigen int vert des chars
    data->c = 'a';
    data->val = (int)data->c;
}

void calc(IntCharPair* data)
{
    //annahme: intChar pair wird um 1 erhöht --> aus a wir b und aus 1 wird 2
    data->val++;
    data->c = (char)data->val;
}

bool check(IntCharPair* data)
{
    if (data->c == 'z') {
        return 0;
    }
    return 1;
}

int main(int argc, char const* argv[])
{
    pid_t pid;

    int pipeChildToParent[2], pipteParentToChild[2];
    //create pipes
    if (pipe(pipeChildToParent) || pipe(pipteParentToChild)) {
        perror("Falied creating pipes");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    //Child
    if (pid == 0) {
        struct IntCharPair data;

        //close pipes
        close(pipeChildToParent[READ]);
        close(pipteParentToChild[WRITE]);

        while (true) {

            read(pipteParentToChild[READ], &data, sizeof(struct IntCharPair));
            printf("Child received: \tc = %c, \tval = %d\n", data.c, data.val);
            calc(&data);
            write(pipeChildToParent[WRITE], &data, sizeof(struct IntCharPair));
            printf("Child sent: \t\tc = %c, \tval = %d\n", data.c, data.val);
        }

        close(pipeChildToParent[WRITE]);
        close(pipteParentToChild[READ]);
        exit(EXIT_SUCCESS);
    }

    //Parent
    if (pid > 0) {
        //initialize struct
        struct IntCharPair data;
        init(&data);

        //close pipes
        close(pipteParentToChild[READ]);
        close(pipeChildToParent[WRITE]);

        while (true) {
            write(pipteParentToChild[WRITE], &data, sizeof(struct IntCharPair));
            printf("Parent sent: \t\tc = %c, \tval = %d\n", data.c, data.val);
            read(pipeChildToParent[READ], &data, sizeof(struct IntCharPair));
            printf("Parent received: \tc = %c, \tval = %d\n", data.c, data.val);

            //check data object
            if (check(&data) == 0) {
                break;
            }
        }
        //kill child
        kill(pid, SIGKILL);
        close(pipeChildToParent[READ]);
        close(pipteParentToChild[WRITE]);
        wait(0);
    }

    //Error
    if (pid < 0) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
