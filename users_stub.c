#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCHARS (200 + 1) // we assume a line in the file has a maximum length of 200 characters + \0

int main(int argc, char* argv[])
{
    FILE* file = fopen("/etc/passwd", "r"); // open file

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // TODO:
    // 1. read each line from from file
    char input[MAXCHARS];
    char* readLine;
    do {
        if (readLine != NULL) {
            char* subName = strchr(input, ':');
            long sizeName = subName - input;
            char name[sizeName + 1];
            memcpy(name, input, sizeName);
            name[sizeName] = '\n';

            char* subID = strchr(subName + 3, ':');
            long sizeID = subID - (subName + 3);
            char id[sizeID + 1];
            memcpy(id, subName + 3, sizeID);
            id[sizeID] = '\n';

            printf("%s,%s\n", id, name);
        }

    } while (readLine != NULL);

    fclose(file);

    // 2. parse for username (first column) and print
    // 3. find third column and print user-id

    // TODO: close file

    return 0;
}
