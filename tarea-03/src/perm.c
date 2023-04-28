#include "perm.h"

int* random_vecc(int n) {
    int* v = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100;
    }
    return v;
}

void perm(int* a, int k, int n) {
    if (k == n) {
        // printf("\n( ");
        for (int i = 0; i < n; i++) {
            // printf("%d ", a[i]);
        }
        // printf(")\n");
        return;
    }
    for (int i = k; i < n; i++) {
        int t = a[k];
        a[k] = a[i];
        a[i] = t;
        perm(a, k + 1, n);
        t = a[k];
        a[k] = a[i];
        a[i] = t;
    }
}

double bench_perm(int* v, int n, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++) {
        perm(v, 0, n);
    }
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

void benchmark_perm(int iters, int factor, int experiment, int scale) {
    int N = factor;
    int* v = NULL;
    double r1;

    double** results = (double**)malloc(2 * sizeof(double*));
    for (int i = 0; i < 2; i++) {
        results[i] = (double*)malloc(iters * sizeof(double));
    }

    printf("Benchmarking permutation O(nn!)...\n");
    printf("N,permutation O(nn!)\n");
    for (int i = 0; i < iters; i++) {
        v = random_vecc(N);
        r1 = 0.0;
        for (int j = 0; j < experiment; j++) {
            r1 += bench_perm(v, N, scale);
        }
        results[0][i] = N;
        results[1][i] = r1 / experiment;
        printf("%d,%f\n", N, r1 / experiment);

        N += factor;
        free(v);
    }

    save_results_perm(results, iters);

    for (int i = 0; i < 2; i++) {
        free(results[i]);
    }
    free(results);
}

void save_results_perm(double** results, int iters) {
    FILE* fp = fopen("benchmark_permutation.csv", "w");
    fprintf(fp, "N,permutation O(nn!)\n");
    for (int i = 0; i < iters; i++) {
        fprintf(fp, "%f,%f\n", results[0][i], results[1][i]);
    }
    fclose(fp);
}