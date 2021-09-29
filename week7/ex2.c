#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    printf("Input the length of array: ");
    scanf("%d", &n);

    while (n <= 0) {
        printf("Input the correct value for the length (integer > 0): ");
        scanf("%d", &n);
    }

    // allocation
    int *array = (int *) calloc(n, sizeof(int));
    
    for (int i = 0; i < n; ++i) {
        array[i] = i;
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    free(array);
    return 0;
}
