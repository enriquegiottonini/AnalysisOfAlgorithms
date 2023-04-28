#include <stdio.h>

#include "fibonacci.h"
#include "matrix.h"
#include "polynomial.h"
#include "sum.h"

void polynomials(void) {
    srand(time(NULL));
    int iters = 20;
    int factor = 500;
    int experiments = 100;
    int scale = 10;
    bench_polyevals(iters, factor, experiments, scale);
}

void fibonacci(void) {
    int iters = 20;
    int factor = 1;
    int experiments = 100;
    int scale = 2000;
    bench_fibonacci(iters, factor, experiments, scale);
}

void sums(void) {
    int iters = 20;
    int factor = 500;
    int experiments = 100;
    int scale = 100;
    bench_sums(iters, factor, experiments, scale);
}

void transposes(void) {
    int iters = 50;
    int factor = 10;
    int experiments = 100;
    int scale = 10;
    bench_matrix_transpose(iters, factor, experiments, scale);
}

void multiplication(void) {
    int iters = 10;
    int factor = 10;
    int experiments = 100;
    int scale = 10;
    bench_matrix_multiplication(iters, factor, experiments, scale);
}

int main(void) {
    // polynomials();
    // fibonacci();
    // sums();
    // transposes();
    multiplication();

    return 0;
}
