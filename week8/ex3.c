#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Analyzing the table which was provided by top command we see:
every second parameters VIRT and RES grows
since program requires more memory every second(using malloc without free).
*/

int main() {
    void* ptr;
    long tenMB = 50 * 1024 * 1024;
    for (int i = 0; i < 20; ++i) {
        ptr = malloc(tenMB);
        memset(ptr, 0, tenMB);
        printf("yet another 10MB is allocated and filled with 0's\n");
        sleep(1);
    }
    return 0;
}
