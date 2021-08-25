#include <stdio.h>

void swap(int *first, int *second) {
    int temp = *second;
    *second = *first;
    *first = temp;
}

int main(int argc, char **argv) {
    int first;
    int second;

    printf("input first number:\n");
    scanf("%d", &first);
    printf("input second number:\n");
    scanf("%d", &second);

    printf("before swap: %d %d\n", first, second);
    swap(&first, &second);
    printf("after swap: %d %d", first, second);

    return 0;
}
