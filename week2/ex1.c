#include <stdio.h>
#include <float.h>
#include <limits.h>

int main() {
    int intMax = INT_MAX;
    double dblMax = DBL_MAX;
    float fltMax = FLT_MAX;

    printf("size of integer %llu", sizeof(intMax));
    printf("max integer is %d", intMax);
    printf("size of double %llu", sizeof(dblMax));
    printf("max integer is %f", dblMax);
    printf("size of float %llu", sizeof(fltMax));
    printf("max integer is %f", fltMax);


    return 0;
}
