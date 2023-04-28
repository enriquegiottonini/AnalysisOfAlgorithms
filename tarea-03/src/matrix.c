#include "matrix.h"

int* random_square_matrix(int n) {
    int* matrix = (int*)malloc(n * n * sizeof(int));
    for (int i = 0; i < n * n; i++)
        matrix[i] = rand();
    return matrix;
}

int* transpose(int* matrix, int n) {
    int* transposed = (int*)malloc(n * n * sizeof(int));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            transposed[row * n + col] = matrix[col * n + row];
        }
    }
    return transposed;
}

int* mult(int* A, int* B, int n) {
    int* C = (int*)malloc(n * n * sizeof(int));
    int sum = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++, sum = 0) {
            for (int i = 0; i < n; i++) {
                sum += A[row * n + i] * B[i * n + col];
            }
            C[row * n + col] = sum;
        }
    }
    return C;
}

void print_matrix(int* matrix, int n) {
    printf("\nMatrix:\n");
    for (int i = 0; i < n * n; i++) {
        printf("%d\t", matrix[i]);
        if ((i + 1) % n == 0)
            printf("\n");
    }
}

void free_matrix(int* matrix) {
    if (matrix != NULL)
        free(matrix);
}

double bench_transpose(int* matrix, int n, int k) {
    clock_t start = clock();
    for (int i = 0; i < k; i++) {
        int* transposed = transpose(matrix, n);
        free_matrix(transposed);
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double bench_mult(int* A, int* B, int n, int k) {
    clock_t start = clock();
    for (int i = 0; i < k; i++) {
        int* C = mult(A, B, n);
        free_matrix(C);
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void bench_matrix_transpose(int iters, int factor, int experiments, int scale) {
    int N = factor;
    int* A = NULL;
    double r1;

    // matrix for storing results
    double** results = (double**)malloc(experiments * sizeof(double*));
    for (int i = 0; i < 2; i++)
        results[i] = (double*)malloc(iters * sizeof(double));

    printf("N,transpose O(n^2)\n");
    for (int i = 0; i < iters; i++) {
        A = random_square_matrix(N);
        r1 = 0.0;
        for (int j = 0; j < experiments; j++) {
            r1 += bench_transpose(A, N, scale);
        }
        results[0][i] = N;
        results[1][i] = r1 / experiments;

        printf("%d,%f\n", N, results[1][i]);

        N += factor;
        free_matrix(A);
    }

    // save results to file
    save_matrix_transpose_results(results, iters, "benchmark_transpose.csv");

    // free memory
    for (int i = 0; i < 2; i++)
        free(results[i]);
    free(results);
}

void save_matrix_transpose_results(double** results, int rows, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(fp, "N,transpose O(n^2)\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%d,%f\n", (int)results[0][i], results[1][i]);
    }

    fclose(fp);
}

void bench_matrix_multiplication(int iters, int factor, int experiments, int scale) {
    int N = factor;
    int* A = NULL;
    int* B = NULL;
    double r1;

    // matrix for storing results
    double** results = (double**)malloc(experiments * sizeof(double*));
    for (int i = 0; i < 2; i++)
        results[i] = (double*)malloc(iters * sizeof(double));

    printf("N,multiplication O(n^3)\n");
    for (int i = 0; i < iters; i++) {
        A = random_square_matrix(N);
        B = random_square_matrix(N);
        r1 = 0.0;
        for (int j = 0; j < experiments; j++) {
            r1 += bench_mult(A, B, N, scale);
        }
        results[0][i] = N;
        results[1][i] = r1 / experiments;

        printf("%d,%f\n", N, results[1][i]);

        N += factor;
        free_matrix(A);
        free_matrix(B);
    }

    // save results to file
    save_matrix_multiplication_results(results, iters, "benchmark_multiplication.csv");

    // free memory
    for (int i = 0; i < 2; i++)
        free(results[i]);
    free(results);
}

void save_matrix_multiplication_results(double** results, int rows, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(fp, "N, multiplication O(n^3)\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%d,%f\n", (int)results[0][i], results[1][i]);
    }

    fclose(fp);
}