#include "sorting_methods.h"

// Auxiliary functions
bool leq(int x, int y) {
    return (x <= y);
}

bool geq(int x, int y) {
    return (x >= y);
}

void printStats(int* (*f)()) {
    size_t N = 100;
    printf("For N=%d\n", (int)N);
    f(NULL, N, leq);
}

int main(void) {
    printStats(merge_sort);
}