#include <stdio.h>

#include "fibonacci.h"
#include "polynomial.h"

void polynomials(void) {
    srand(time(NULL));
    int iters = 10;
    int factor = 1000;
    int experiments = 1;
    int scale = 1;
    bench_polyevals(iters, factor, experiments, scale);
}

void fibonacci(void) {
    int iters = 20;
    int factor = 1;
    int experiments = 100;
    int scale = 2000;
    bench_fibonacci(iters, factor, experiments, scale);
}

int main(void) {
    polynomials();
    // fibonacci();

    return 0;
}
