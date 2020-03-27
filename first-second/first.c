#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 100000


int main(int argc, char** argv)
{
    int vals[NUM];

    FILE* fpIn = fopen("/dev/urandom", "rb");
    for (int i = 0; i < NUM; i++)
    {
        fread(vals + i, sizeof(int), 1, fpIn);
    }
    fclose(fpIn);

    FILE* fpOut = fopen("out.first", "w");
    for (int i = 0; i < NUM; i++)
    {
        vals[i] = fabsf(vals[i]);
        fwrite(vals + i, sizeof(int), 1, fpOut);
    }
    fclose(fpOut);

    return EXIT_SUCCESS;
}
