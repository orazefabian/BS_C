#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 10

void
printArr(int arr[], int index)
{
  for (int i = index; i < MAXLEN; ++i) {
    printf("Fibonacci at index: [%d] = %d\n", i, arr[i]);
  }
}

int
main(int argc, char const* argv[])
{
  srand(time(0));
  int arrfib[MAXLEN];
  arrfib[0] = 0;
  arrfib[1] = 1;

  for (int i = 2; i < MAXLEN; ++i) {
    arrfib[i] = arrfib[i - 1] + arrfib[i - 2];
  }

  int start = rand() % 9;
  printf("Random start point = %d\n", start);
  printArr(arrfib, start);

  return 0;
}
