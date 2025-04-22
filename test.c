#include <stdlib.h>
#include <stdio.h>

typedef struct testStruct {
    char first;
} test;

int main() {
    printf("%d\n",sizeof(test));
    return 0;
}