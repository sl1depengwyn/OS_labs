#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char command[64];
    for (;;) {
	printf("$ ");
        scanf("%s", command);
        system(command);
    }
    return EXIT_SUCCESS;
}

