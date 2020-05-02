#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    //create named pipe and check if successful
    if (mkfifo("thePipe", 0664) == -1) {
        perror("Pipe creation failed!");
    }

    //open pipe with write permission
    FILE* thepipe = fopen("thePipe", "w");
    if (thepipe == NULL) {
        perror("Could not open pipe!");
        exit(EXIT_FAILURE);
    }

    int buffer;

    srand(time(NULL));

    //write random int values to pipe
    for (int i = 0; i < 1 + (rand() % 10); i++) {
        buffer = rand() % 100;
        fwrite(&buffer, sizeof(int), 1, thepipe);
        fprintf(stdout, "producer writes: %i\n", buffer);
        fflush(thepipe);
        sleep(1);
    }
    fclose(thepipe);

    return EXIT_SUCCESS;
}
