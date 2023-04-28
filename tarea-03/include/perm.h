#ifndef PERM_H
#define PERM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *random_vecc(int);
void perm(int *, int, int);
double bench_perm(int *v, int n, int k);
void benchmark_perm(int, int, int, int);
void save_results_perm(double **results, int iters);

#endif
