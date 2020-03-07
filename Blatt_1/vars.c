#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGLENGTH 16

int main(int argc, char const *argv[]) {
  double num1;
  unsigned int num2;
  char c;
  char string[STRINGLENGTH];
  long long int num3;

  printf("Enter character:\n");
  scanf(" %c", &c);
  printf("%c\n", c);
  printf("size: %ld\n", sizeof(c));

  printf("\nEnter double:\n");
  scanf("%lf", &num1);
  printf("%lf\n", num1);
  printf("size: %ld\n", sizeof(num1));

  printf("\nEnter int:\n");
  scanf("%d", &num2);
  printf("%d\n", num2);
  printf("size: %ld\n", sizeof(num2));

  printf("\nEnter long:\n");
  scanf("%lli", &num3);
  printf("%lli\n", num3);
  printf("size: %ld\n", sizeof(num3));

  printf("\nEnter string\n");
  getchar();
  fgets(string, STRINGLENGTH, stdin);
  printf("%s\n", string);
  printf("size: %ld\n", sizeof(string));
}
