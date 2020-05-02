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
    //open pipe with read permission
    FILE* thepipe = fopen("thePipe", "r");

    if (thepipe == NULL) {
        perror("Could not open pipe!");
        exit(EXIT_FAILURE);
    }

    int min = __INT32_MAX__, max = 0, count = 0, buffer;
    float sum = 0, avg = 0;

    //read values from pipe
    while (fread(&buffer, sizeof(int), 1, thepipe) == 1) {
        if (min > buffer) {
            min = buffer;
        }
        if (max < buffer) {
            max = buffer;
        }
        count++;
        sum += buffer;
        avg = sum / count;
    }
    /* TODO calculate result and display the result on the screen */
    printf("min: %i, max: %i, sum: %f, avg: %f\n", min, max, sum, avg);

    fclose(thepipe);

    return EXIT_SUCCESS;
}
