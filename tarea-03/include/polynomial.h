#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

double irand(void);
int *random_vector(int);
double polyeval_bruteforce_v1(double x, int *coeffs, int n);
double polyeval_bruteforce_v2(double x, int *coeffs, int n);
double polyeval_horner(double x, int *coeffs, int degree);
double bench_bruteforce_v1(double, int *, int, int);
double bench_bruteforce_v2(double, int *, int, int);
double bench_horner(double, int *, int, int);
void bench_polyevals(int, int, int, int);
void save_polynomial_results(double **results, int iters, char *filename);
#endif
