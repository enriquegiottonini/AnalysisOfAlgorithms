#include "fibonacci.h"

unsigned int recursive_fibonacci(unsigned int N) {
    if (N <= 0)
        return 0;
    else if (N == 1)
        return 1;

    return recursive_fibonacci(N - 1) + recursive_fibonacci(N - 2);
}

unsigned int recursive_memoized_fibonacci(unsigned int N) {
    if (N <= 0)
        return 0;
    else if (N == 1)
        return 1;

    unsigned int *memo = (unsigned int *)malloc((N + 1) * sizeof(unsigned int));
    for (unsigned int i = 0; i <= N; i++)
        memo[i] = 0;

    unsigned int result = memoized_helper(N, memo);
    free(memo);
    return result;
}

unsigned int memoized_helper(unsigned int N, unsigned int *memo) {
    if (N <= 0)
        return 0;
    else if (N == 1)
        return 1;

    if (memo[N] == 0)
        memo[N] = memoized_helper(N - 1, memo) + memoized_helper(N - 2, memo);

    return memo[N];
}

unsigned int iterative_fibonacci(unsigned int N) {
    if (N <= 0)
        return 0;

    unsigned int prev, curr, temp;
    prev = curr = 1;
    for (unsigned int i = 2; i < N; i++) {
        temp = curr;
        curr = prev + curr;
        prev = temp;
    }
    return curr;
}

double bench_recur_fib(unsigned int N, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        recursive_fibonacci(N);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_iter_fib(unsigned int N, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        iterative_fibonacci(N);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_memo_fib(unsigned int N, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        recursive_memoized_fibonacci(N);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

void bench_fibonacci(int iters, int factor, int experiments, int scale) {
    double r1, r2, r3;
    double **results = (double **)malloc(4 * sizeof(double *));
    for (int i = 0; i < 4; i++)
        results[i] = (double *)malloc(iters * sizeof(double));

    printf("Benchmarking fibonacci functions:\n");
    printf("Scale: %d\n", scale);
    printf("Experiments: %d\n", experiments);
    printf("N, recursive, iterative, memoized\n");

    for (int i = 0; i < iters; i++) {
        r1 = r2 = r3 = 0;
        for (int j = 0; j < experiments; j++) {
            r1 += bench_recur_fib((i + 1) * factor, scale);
            r2 += bench_iter_fib((i + 1) * factor, scale);
            r3 += bench_memo_fib((i + 1) * factor, scale);
        }

        results[0][i] = (i + 1) * factor;
        results[1][i] = r1 / experiments;
        results[2][i] = r2 / experiments;
        results[3][i] = r3 / experiments;

        printf("%d, %lf, %lf, %lf\n", (int)results[0][i], results[1][i], results[2][i], results[3][i]);
    }

    save_fibonacci_results(results, iters, "benchmark_fibonacci.csv");

    // free memory
    free(results[0]);
    free(results[1]);
    free(results);
}

void save_fibonacci_results(double **results, int iters, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp, "N, recursive, iterative, memoized\n");
    for (int i = 0; i < iters; i++)
        fprintf(fp, "%d, %lf, %lf, %lf\n", (int)results[0][i], results[1][i], results[2][i], results[3][i]);
    fclose(fp);
}