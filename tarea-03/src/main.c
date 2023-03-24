#include <stdio.h>

#include "addition_algos.h"

int main(void) {
    int a = 2, b = 4;
    printf("The sum of %d and %d is %d.\n", a, b, add(a, b));
    return 0;
}