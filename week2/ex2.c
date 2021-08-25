#include <stdio.h>
#include <string.h>

int main() {
    char* string;


    printf("type a string:\n");

    scanf("%s", string);

    for (int i = strlen(string) - 1; i >= 0; --i) {
        printf("%c", string[i]);
    }

    return 0;
}
