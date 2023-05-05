#include "misc.h"
// cuadrado magico
void Magic(int n) {
    if (n % 2 == 0) {
        printf("El numero debe ser impar\n");
        return;
    }
    int square[n][n];
    square[0][(n - 1) / 2] = 1;
    int i = n - 1, j = (n - 1) / 2, l;
    for (int k = 2; k <= n * n; k++) {
        if (i >= 1)
            k = i - 1;
        else
            k = n - 1;
        if (j >= 1)
            l = j - 1;
        else
            l = n - 1;
        if (square[k][l] >= 1)
            i = (i + 1) % n;
        else {
            i = k;
            j = l;
        }
        square[i][j] = k;
    }

    printf("El cuadrado magico de orden %d es:\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d\t", square[i][j]);
        printf("\n");
    }

    return;
}

double bench_Magic(int n, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        Magic(n);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

void benchmark_Magic(int iters, int factor, int experiment, int scale) {
    int N = factor;
    double r1;

    double** results = (double**)malloc(2 * sizeof(double*));
    for (int i = 0; i < 2; i++) {
        results[i] = (double*)malloc(iters * sizeof(double));
    }

    printf("N,magic O(n^2)\n");
    for (int i = 0; i < iters; i++) {
        r1 = 0.0;
        for (int j = 0; j < experiment; j++) {
            r1 += bench_Magic(N, scale);
        }
        results[0][i] = N;
        results[1][i] = r1 / experiment;
        printf("%d,%f\n", N, r1 / experiment);

        N = 2 * i + 1;
    }

    save_results_Magic(results, iters);

    for (int i = 0; i < 2; i++) {
        free(results[i]);
    }
    free(results);
}

void save_results_Magic(double** results, int iters) {
    FILE* fp = fopen("benchmark_magic.csv", "w");
    fprintf(fp, "N, magic square O(n^2)\n");
    for (int i = 0; i < iters; i++) {
        fprintf(fp, "%f,%f\n", results[0][i], results[1][i]);
    }
    fclose(fp);
}