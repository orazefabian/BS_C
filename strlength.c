#include "strlength.h"
#include <stdio.h>

//function definition
unsigned int strlength(char* str)
{
    unsigned int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}