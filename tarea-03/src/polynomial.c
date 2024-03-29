#include "polynomial.h"

double irand() {
    double r = -1 + 2 * ((double)rand()) / RAND_MAX;
    return r;
}

int *random_vector(int n) {
    int *vect = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        vect[i] = rand();
    return vect;
}

double power(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++)
        result *= x;
    return result;
}

double polyeval_bruteforce_v0(double x, int *coefficients, int degree) {
    double result = 0;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * power(x, i);
    }
    return result;
}

double polyeval_bruteforce_v1(double x, int *coefficients, int degree) {
    double result = 0;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * pow(x, i);
    }
    return result;
}

double polyeval_bruteforce_v2(double x, int *coeffs, int degree) {
    double result = 0;
    double xth = 1.0;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * xth;
        xth *= x;
    }
    return result;
}

double polyeval_horner(double x, int *coeffs, int degree) {
    double result = 0;
    for (int i = degree + 1; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    return result;
}

double bench_bruteforce_v0(double x, int *coeffs, int degree, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        polyeval_bruteforce_v0(x, coeffs, degree);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_bruteforce_v1(double x, int *coeffs, int degree, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        polyeval_bruteforce_v1(x, coeffs, degree);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_bruteforce_v2(double x, int *coeffs, int degree, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        polyeval_bruteforce_v2(x, coeffs, degree);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

double bench_horner(double x, int *coeffs, int degree, int k) {
    double start_time, end_time, time_elapsed;
    start_time = (double)clock() / CLOCKS_PER_SEC;
    for (int i = 0; i < k; i++)
        polyeval_horner(x, coeffs, degree);
    end_time = (double)clock() / CLOCKS_PER_SEC;
    time_elapsed = end_time - start_time;
    return time_elapsed;
}

void bench_polyevals(int iters, int factor, int experiments, int scale) {
    int N = factor;
    int *coeffs = NULL;
    double x, r0, r1, r2, r3;

    // matrix for saving results
    double **results = (double **)malloc(iters * sizeof(double *));
    for (int j = 0; j < 5; j++)
        results[j] = (double *)malloc(iters * sizeof(double));

    printf("N,bruteforce_v0,bruteforce_v1,bruteforce_v2,horner\n");
    for (int i = 0; i < iters; i++) {
        coeffs = random_vector(N + 1);
        x = irand();
        r0 = r1 = r2 = r3 = 0.0;
        for (int j = 0; j < experiments; j++) {
            r0 += bench_bruteforce_v0(x, coeffs, N, scale);
            r1 += bench_bruteforce_v1(x, coeffs, N, scale);
            r2 += bench_bruteforce_v2(x, coeffs, N, scale);
            r3 += bench_horner(x, coeffs, N, scale);
        }
        results[0][i] = (i + 1) * factor;
        results[1][i] = r0 / experiments;
        results[2][i] = r1 / experiments * 100;
        results[3][i] = r2 / experiments * 100;
        results[4][i] = r3 / experiments * 100;

        printf("%d,%f,%f,%f,%f\n", N, r0 / experiments, r1 / experiments, r2 / experiments, r3 / experiments);

        N += factor;

        if (coeffs != NULL)
            free(coeffs);
        coeffs = NULL;
    }

    save_polynomial_results(results, iters, "benchmark_polynomials.csv");

    for (int j = 0; j < 5; j++)
        free(results[j]);
    free(results);
}

void save_polynomial_results(double **results, int rows, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // write results to file
    fprintf(fp, "N,bruteforce O(n^2), bruteforce O(nlog(n)), efficient bruteforce O(n), horner O(n)\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%d,%f,%f,%f,%f\n", (int)results[0][i], results[1][i],
                results[2][i], results[3][i], results[4][i]);
    }
    fclose(fp);
}
