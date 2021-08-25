#include <stdio.h>

int main(int argc, char **argv) {
    int n;
    int fig;
    if (argc == 1) {
        printf("run the program with parameter n that is equal to height of a triangle");
    } else if (argc == 2) {
        printf("you can specify the figure by adding another parameter: 1 - right angle triangle, 2 - triangle with its base on the right, 3 - square");
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
    } else {
        sscanf(*(argv+1), "%d", &n);
        sscanf(*(argv+2), "%d", &fig);
        switch (fig) {
            case 1:
                for (int height = 1; height <= n; ++height) {
                    for (int stars = 0; stars < height; ++stars) {
                        printf("*");
                    }
                    printf("\n");
                }
                break;
            case 2:
                n++;
                for (int height = 0; height < n; ++height) {
                    if (height < (n / 2 + n % 2)) {
                        for (int stars = 0; stars < height; ++stars) {
                            printf("*");
                        }
                    } else {
                        for (int stars = 0; stars < n - height; ++stars) {
                            printf("*");
                        }
                    }
                    printf("\n");
                }
                break;
            case 3:
                for (int height = 1; height <= n; ++height) {
                    for (int stars = 0; stars < n; ++stars) {
                        printf("*");
                    }
                    printf("\n");
                }
                break;
            default:
                printf("available parameters: 1 - right angle triangle, 2 - triangle with its base on the right, 3 - square\nothers will be added later");
                break;
        }
    }
    return 0;
}
