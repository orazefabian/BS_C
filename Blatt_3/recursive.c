#include <stdio.h>

static unsigned cnt = 0;

void foo();

int main(int argc, char const* argv[])
{
    foo();
    return 0;
}

void foo()
{
    char a[2000] = "It works!";
    if (10000 > ++cnt) {
        foo();
    } else {
        printf("%u %s\n", cnt, a);
    }
}