#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

void signalHandler(int signum)
{
    if (signum == SIGUSR1) {
        syslog(LOG_INFO, "SIGUSR1");
    }
}

int main(void)
{

    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
           we can exit the parent process. */
    if (pid > 0) {
        printf("Send singal to Deamon process('s' for SIGUSR1 signal or 'q' to quit the deamon: ");
        while (true) {
            char sig;
            scanf("%c", &sig);
            if (sig == 's') {
                kill(pid, SIGUSR1);
            }
            if (sig == 'q') {
                kill(pid, SIGKILL);
                break;
            }
        }

        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */
    openlog("Deamon Log", LOG_PID, LOG_INFO);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* The Big Loop */
    while (1) {
        /* Do some task here ... */
        signal(SIGUSR1, signalHandler);
        sleep(30); /* wait 30 seconds */
    }
    closelog();
    exit(EXIT_SUCCESS);
}