#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCHARS \
    (200 + 1) // we assume a line in the file has a maximum length of 200 characters + \0

int main(int argc, char* argv[])
{

    int option_index = 0;
    FILE* output_file = stdout;

    FILE* file = fopen("/etc/passwd", "r"); // open file

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char input[MAXCHARS];
    char* readLine;

    while ((option_index = getopt(argc, argv, "o:")) != -1) {
        switch (option_index) {
        case 'o':
            output_file = fopen(optarg, "w");
            break;
        case '?': //unknown option
            printf("Option not known\n");
            return 1;
        default:
            return 0;
        }
    }

    do {
        readLine = fgets(input, MAXCHARS, file);
        // if it reads a comment it skips that line
        if (readLine != NULL && input[0] != '#') {
            char* subName = strchr(input, ':');
            long nameSize = subName - input;
            char name[nameSize + 1];
            memcpy(name, input, nameSize);

            //correct "_" before each username
            if (name[0] == '_') {
                for (int i = 0; i < nameSize; i++) {
                    name[i] = name[i + 1];
                }
                name[nameSize - 1] = '\0';
            } else {
                name[nameSize] = '\0';
            }

            char* subID = strchr(subName + 3, ':');
            long idSize = subID - (subName + 3);
            char id[idSize + 1];
            memcpy(id, subName + 3, idSize);
            id[idSize] = '\0';

            fprintf(output_file, "%s %s\n", id, name);
        }

    } while (readLine != NULL);

    fclose(file);
    fclose(output_file);

    return 0;
}
