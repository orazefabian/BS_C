#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSGTYPE 1

typedef struct msgbuf_s {
    long mtype; /* message type, must be > 0 */
    long mtext; /* message data */
} msgbuf_t;

int coll(int n);

int main(int argc, char** argv)
{
    /* check argument */
    int num = (argc == 2) ? atoi(argv[1]) : 0;

    if (num < 1) {
        printf("Arguments where not correct:\n");
        printf("Usage: ./main <n> // 0 < n\n");
        exit(EXIT_FAILURE);
    }

    int msgID = msgget(IPC_PRIVATE, IPC_CREAT | 0644);
    msgbuf_t buffer;
    buffer.mtype = MSGTYPE;
    buffer.mtext = num;

    pid_t pid = fork();
    if (pid < (pid_t)0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    }
    if (pid == (pid_t)0) { // child

        // Calculate Collatz
        while (buffer.mtext != 1) {
            buffer.mtext = coll(buffer.mtext);
            msgsnd(msgID, &buffer, sizeof(buffer), IPC_SET);
        }

        // Send collatz to parent
        exit(EXIT_SUCCESS);
    }

    // parent
    do {
        msgrcv(msgID, &buffer, sizeof(buffer), MSGTYPE, IPC_SET);
        printf("parent: coll: %ld\n", buffer.mtext);
    } while (buffer.mtext != 1);

    waitpid(pid, NULL, 0);
    msgctl(msgID, IPC_RMID, 0);

    return EXIT_SUCCESS;
}

int coll(int n) { return (n % 2 == 1) ? n * 3 + 1 : n / 2; }