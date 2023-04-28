#ifndef SUM_H
#define SUM_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sum(int *, int);
int rsum(int *, int);
double bench_sum(int *, int, int);
double bench_rsum(int *, int, int);
void bench_sums(int, int, int, int);
void save_sums_results(double **results, int rows, char *filename);

#endif