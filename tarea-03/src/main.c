#include <stdio.h>

#include "fibonacci.h"
#include "matrix.h"
#include "misc.h"
#include "perm.h"
#include "polynomial.h"
#include "search.h"
#include "sum.h"

void polynomials(void) {
    srand(time(NULL));
    int iters = 20;
    int factor = 500;
    int experiments = 100;
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

void permutations(void) {
    int iters = 10;
    int factor = 1;
    int experiments = 10;
    int scale = 10;
    benchmark_perm(iters, factor, experiments, scale);
}

void search(void) {
    int iters = 10;
    int factor = 100;
    int experiments = 100;
    int scale = 1000;
    benchmark_search(iters, factor, experiments, scale);
}

void magic_square(void) {
    int iters = 1;
    int factor = 3;
    int experiments = 1;
    int scale = 1;
    benchmark_Magic(iters, factor, experiments, scale);
}

int main(void) {
    polynomials();
    // fibonacci();
    // sums();
    // transposes();
    // multiplication();
    // permutations();
    // search();
    magic_square();

    return 0;
}
