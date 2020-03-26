#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCHARS \
    (200 + 1) // we assume a line in the file has a maximum length of 200 characters + \0
#define MAXLINE 30 //max amount of read lines

void printArray(char** arr, int size);

int main(int argc, char* argv[])
{
    FILE* file = fopen("/etc/passwd", "r"); // open file

    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char* input = (char*)malloc(sizeof(char) * MAXCHARS);
    //initialize dynamic array
    char** arr = (char**)malloc(sizeof(char*) * MAXLINE);
    char* readLine;
    int lineLength;
    int index = 0; //to keep track of array i

    for (int i = 0; i < MAXLINE + 10; i++) { //because first 10 lines are comments
        readLine = fgets(input, MAXCHARS, file);
        if (readLine != NULL && input[0] != '#') {

            lineLength = strlen(readLine);
            arr[index] = (char*)malloc((lineLength) * sizeof(char)); //give just enough space
            memcpy(arr[index], readLine, lineLength);
            arr[index][lineLength] = '\0';
            index++;
        }
    }
    printArray(arr, MAXLINE);

    //free memory
    for (int i = 0; i < MAXLINE; i++) {
        free(arr[i]);
    }
    free(arr);
    fclose(file);

    return EXIT_SUCCESS;
}

void printArray(char** arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d  %s", i, arr[i]);
    }
}
