#include "sum.h"

int *random_vec(int n) {
    int *vect = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        vect[i] = rand() % 100;
    return vect;
}

int sum(int *nums, int n) {
    int result = 0;
    for (int i = 0; i < n; i++)
        result += nums[i];
    return result;
}

int rsum(int *nums, int n) {
    if (n == 0)
        return 0;
    else
        return nums[n - 1] + rsum(nums, n - 1);
}

double bench_sum(int *nums, int n, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        sum(nums, n);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_rsum(int *nums, int n, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        rsum(nums, n);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

void bench_sums(int iters, int factor, int experiments, int scale) {
    int N = factor;
    int *nums = NULL;
    double r1, r2;

    // matrix for storing results
    double **results = (double **)malloc(3 * sizeof(double *));
    for (int i = 0; i < 3; i++)
        results[i] = (double *)malloc(iters * sizeof(double));

    for (int i = 0; i < iters; i++) {
        nums = random_vec(N);
        r1 = r2 = 0.0;
        for (int j = 0; j < experiments; j++) {
            r1 += bench_sum(nums, N, scale);
            r2 += bench_rsum(nums, N, scale);
        }
        results[0][i] = N;
        results[1][i] = r1 / experiments;
        results[2][i] = r2 / experiments;
        N += factor;
        free(nums);
    }

    // save results to file
    save_sums_results(results, iters, "benchmark_sums.csv");

    // free memory
    for (int i = 0; i < 3; i++)
        free(results[i]);
    free(results);
}

void save_sums_results(double **results, int rows, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(fp, "N,sum O(n),rsum O(n)\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%d,%f,%f\n", (int)results[0][i], results[1][i], results[2][i]);
    }

    fclose(fp);
}