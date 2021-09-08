#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    int n = 10;
    for (int i = 0; i < n; ++i) {
        if (pid == 0) {
            printf("Hello from child [%d - %d]\n", pid, i);
        } else if (pid > 0) {
            printf("Hello from parent [%d - %d]\n", pid, i);
        } else {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
    return 0;
}

/*
Explanations:
On my machine I see
Hello from parent [PID - i]
Hello from child [0 - i]
each after another and then
Hello from parent [PID+2 - i]
Hello from child [0 - i]
Another 10 lines of output, but 
PID increased by 2 since PID+1 is 
taken by child of the parent of the 
previous instance of the program
*/

