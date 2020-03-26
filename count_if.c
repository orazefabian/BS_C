#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool (*IntFunction)(int);
bool isEven(int value);
bool isGreaterThanPrevious(int value);
void printArr(int arr[]);
unsigned count_if(int array[], unsigned size, IntFunction func);

static int previous = 0; //to save previous state

int main(int argc, char const* argv[])
{
    //create fib numbers in array
    int* fibArr = (int*)malloc(sizeof(int) * 10);
    fibArr[0] = 0;
    fibArr[1] = 1;
    for (int i = 2; i < 10; i++) {
        fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
    }

    unsigned countEven = count_if(fibArr, 10, isEven);
    unsigned countGreater = count_if(fibArr, 10, isGreaterThanPrevious);
    printArr(fibArr);
    printf("\n#isEven: %u", countEven);
    printf("\n#isGreaterThanPrevious: %u\n", countGreater);

    return 0;
}

unsigned count_if(int array[], unsigned size, IntFunction func)
{
    unsigned count = 0;
    for (int i = 0; i < size; i++) {
        if ((func)(array[i])) {
            count++;
        }
    }
    return count;
}

bool isEven(int value)
{
    if (value % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

bool isGreaterThanPrevious(int value)
{
    bool greater = value > previous;
    previous = value;

    return greater;
}

void printArr(int arr[])
{
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
}
