#include <stdio.h>
#include <stdlib.h>

static int cnt = 0;

/// Read `cnt` Integers into given array.
/// Returns number of entered zeros.
///
int* readInts(int* arr)
{
    int i = 0;
    int* zeros = (int*)malloc(sizeof(int));

    while (i <= cnt) {
        scanf("%d", arr++);
        if (arr[i++] == 0) {
            *zeros++;
        }
    }
    return zeros;
}

/// Create "double-sized" copy of array (duplicate each value)
///
void extend(int* arr, int* newarr)
{
    newarr = (int*)malloc(2 * cnt * sizeof(int*));
    for (int i = 0, j = 0; i <= cnt; i++) {
        newarr[j++] = arr[i];
        newarr[j++] = arr[i];
    }
}

int main(int argc, char* argv[])
{
    int arr[4];
    int* zeros;

    printf("How many integers (3 or 4)?\n");
    scanf("%d", &cnt);

    zeros = readInts(arr);
    printf("You entered %d zero(s)!\n", *zeros);

    int* newarr;
    extend(arr, newarr);

    for (int i = 0; i < cnt * 2; i++) {
        printf("%d ", newarr[i]);
    }
    printf("\n");

    return 0;
}
