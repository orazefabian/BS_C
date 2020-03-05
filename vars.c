#include <stdio.h>
int main(int argc, char const *argv[]) {
  double num1;
  unsigned int num2;
  char c;
  char string[16];
  long long int num3;

  printf("Enter character:\n");
  scanf(" %c", &c);
  printf("%c\n", c);
  printf("size: %ld\n", sizeof(c));

  printf("Enter double:\n");
  scanf("%lf", &num1);
  printf("%lf\n", num1);
  printf("size: %ld\n", sizeof(num1));

  printf("Enter int:\n");
  scanf("%d", &num2);
  printf("%d\n", num2);
  printf("size: %ld\n", sizeof(num2));

  printf("Enter long:\n");
  scanf("%lli", &num3);
  printf("%lli\n", num3);
  printf("size: %ld\n", sizeof(num3));

  printf("Enter string\n");
  scanf("%15s", string);
  printf("%s\n", string);
  printf("size: %ld\n", sizeof(string));
}
