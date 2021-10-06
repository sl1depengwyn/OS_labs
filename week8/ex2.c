#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
In my case the amount of virtual memory used is 0 (spwd == 0).
Also, there was always si == so == 0. It means that there was no swapped memory.
*/

int main() {
    void* ptr;
    long tenMB = 10 * 1024 * 1024;
    for (int i = 0; i < 20; ++i) {
        ptr = malloc(tenMB);
        memset(ptr, 0, tenMB);
        printf("yet another 10MB is allocated and filled with 0's\n");
        sleep(1);
    }
    return 0;
}

