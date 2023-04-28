#ifndef FIBONACCI_H
#define FIBONACCI_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int recursive_fibonacci(unsigned int);
unsigned int iterative_fibonacci(unsigned int);
unsigned int recursive_memoized_fibonacci(unsigned int);
unsigned int memoized_helper(unsigned int, unsigned int *);
double bench_recur_fib(unsigned int, int);
double bench_iter_fib(unsigned int, int);
double bench_memo_fib(unsigned int, int);
void bench_fibonacci(int, int, int, int);
void save_fibonacci_results(double **, int, char *);

#endif
