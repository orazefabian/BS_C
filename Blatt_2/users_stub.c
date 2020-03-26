#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCHARS \
    (200 + 1) // we assume a line in the file has a maximum length of 200 characters + \0

int main(int argc, char* argv[])
{
    FILE* file = fopen("/etc/passwd", "r"); // open file

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char input[MAXCHARS];
    char* readLine;

    do {
        readLine = fgets(input, MAXCHARS, file);
        // if it reads a comment it skips that line
        if (readLine != NULL && input[0] != '#') {
            char* subName = strchr(input, ':');
            long nameSize = subName - input;
            char name[nameSize + 1];
            memcpy(name, input, nameSize);
            name[nameSize] = '\0';

            char* subID = strchr(subName + 3, ':');
            long idSize = subID - (subName + 3);
            char id[idSize + 1];
            memcpy(id, subName + 3, idSize);
            id[idSize] = '\0';

            printf("%s,%s\n", id, name);
        }

    } while (readLine != NULL);

    fclose(file);

    return 0;
}
