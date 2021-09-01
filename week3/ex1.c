#include <stdio.h>

int main() {
    int *pc;
    int c;
    c = 22;
    printf("Adress of c:%d\n", &c);
    printf("Value of c:%d\n\n", c);
    pc = &c;
    printf("Adress of pointer pc:%d\n", pc);
    printf("Content of pointer pc:%d\n\n", *pc);
    c = 11;
    printf("Adress of pointer pc:%d\n", pc);
    printf("Content of pointer pc:%d\n\n", *pc);
    *pc = 2;
    printf("Addres of c:%d\n", &c);
    printf("Value of c:%d\n\n", c);
    return 0;
}