#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//Zombie: child terminates and has not been waited for
int main(int argc, char const* argv[])
{
    pid_t pids[10];

    for (int i = 0; i < 10; i++) {
        pids[i] = fork();

        if (pids[i] == 0) {
            //child terminates
            exit(0);
        }
    }
    //parent sleeps
    sleep(1000);
    return 0;
}
