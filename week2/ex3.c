#include <stdio.h>

int main(int argc, char **argv) {
    int n = 1;
    if (argc == 1) {
        printf("run the program with parameter n that is equal to height of a triangle");
    } else {
        printf(" \n");
        sscanf(*(argv+1), "%d", &n);
        for (int height = 0; height < n; ++height) {
            for (int spaces = 1; spaces < n - height; ++spaces) {
                printf(" ");
            }
            for (int stars = 0; stars < height; ++stars) {
                printf("*");
            }
            printf("*");
            for (int stars = 0; stars < height; ++stars) {
                printf("*");
            }
            printf("\n");
        }
    }
    return 0;
}
