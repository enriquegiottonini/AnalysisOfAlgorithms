#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* random_square_matrix(int n);
int* transpose(int* matrix, int n);
int* mult(int* A, int* B, int n);
double bench_transpose(int* matrix, int n, int k);
double bench_mult(int* A, int* B, int n, int k);
void bench_matrix_transpose(int iters, int factor, int experiments, int scale);
void save_matrix_transpose_results(double** results, int iters, char* filename);
void bench_matrix_multiplication(int iters, int factor, int experiments, int scale);
void save_matrix_multiplication_results(double** results, int iters, char* filename);
void print_matrix(int* matrix, int n);
void free_matrix(int* matrix);

#endif  // MATRIX_H