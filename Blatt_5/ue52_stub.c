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
#include <unistd.h>


int main(int argc, char** argv)
{
    /* ----------------------------- */
    /* step 0: check input arguments */
    /* TODO -- check for any input arguments, especially for -h and --help
     *         print usage information to dispay if required
     */

    /* ----------------------------- */
    /* step 1: some variables ...    */
    pid_t pid;

    /* ------------------------------ */
    /* step 3: do the work ...        */
    /* step 3.1: create new process via fork */
    /* TODO fork() */

    /* step 3.2: provide code for the parent process */
    /* TODO pid > (pid_t)0 */

    /* step 3.3: provide code for the child process */
    /* TODO pid == (pid_t)0 */

    /* step 3.4: code for the error case, i.e., fork failed */
    /* TODO pid < (pid_t)0 */

    return EXIT_SUCCESS;
};