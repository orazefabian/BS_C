#include "strlength.h"
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

    //check what OS is used and set counter right (passwd file looks different on linux and mac)
    int loopCount;
    char os;
    printf("Enter OS: Linux or MacOS (l) or (m): ");
    scanf(" %c", &os);
    if (os == 'm') {
        loopCount = MAXLINE + 10;
    } else if (os == 'l') {
        loopCount = MAXLINE;
    }

    for (int i = 0; i < loopCount; i++) { //because first 10 lines are comments
        readLine = fgets(input, MAXCHARS, file);
        if (readLine != NULL && input[0] != '#') {

            lineLength = strlen(readLine);

            //correct "_" before lines
            if (readLine[0] == '_') {
                for (int j = 0; j < lineLength; j++) {
                    readLine[j] = readLine[j + 1];
                }
                readLine[lineLength - 1] = '\0';
            } else {
                readLine[lineLength] = '\0';
            }

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
    free(input);
    fclose(file);

    return EXIT_SUCCESS;
}

void printArray(char** arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d  %s", i + 1, arr[i]);
    }
}
