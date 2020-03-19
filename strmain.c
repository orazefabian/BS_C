#include "strlength.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("length of the given string: %u\n", strlength(argv[1]));
    return 0;
}
