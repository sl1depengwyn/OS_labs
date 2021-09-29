#include <stdlib.h>
# include <stdio.h>

int main() {
    char **s;
    char foo[] = "Hello World";
    // here we had not yet initialized value of s, hence when we try to access it *s we get segfault
    // *s = foo;
    s = (char**) malloc(sizeof(char**));
    *s = foo;
    printf("s is %s\n", *s);
    s[0] = foo;
    printf("s [0] is %s\n", s[0]);
    return (0);
}

