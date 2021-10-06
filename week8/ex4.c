#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>

int main() {
    struct rusage usage;
    void* ptr;
    long tenMB = 10 * 1024 * 1024;
    printf("time\tmax resident\tshared memory\tunshared data size\tunshared stack size\n");
    for (int i = 0; i < 10; ++i) {
        ptr = malloc(tenMB);
        memset(ptr, 0, tenMB);
        getrusage(RUSAGE_SELF, &usage);
        printf("%ld.%06lds\t%ld\t\t%ld\t\t%ld\t\t%ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec, usage.ru_maxrss, usage.ru_ixrss, usage.ru_idrss, usage.ru_isrss);
        sleep(1);
    }
    return 0;
}

