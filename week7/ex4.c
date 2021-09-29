#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* my_realloc(void* ptr, int size);

int main() {

    return 0;
}

void* my_realloc(void* ptr, int size) {
    if (ptr) {
        if (size <= 0) {
            free(ptr);
            return NULL;
        } else {
            void *new_ptr = malloc(size);
            // if old size was less than the new one, in fact we will
            // fill ptr to return with some uninitialized values
            void *to_return = memcpy(new_ptr, ptr, size);
            free(ptr);
            return to_return;
        }
    } else {
        if (size <= 0) {
            return NULL;
        } else {
            return malloc(size);
        }
    }
}
