#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "fibonacci.h"
#include "matrix.h"
#include "perm.h"
#include "polynomial.h"
#include "sum.h"
/*
Cortesía de nuestro querido maestro de Estructura de Datos:
Prof. Eduardo Acuña.

Macros para organizar pruebas.

Las pruebas se escriben con check(expresión, mensaje), una prueba
pasa cuando la expresión tiene valor verdadero y falla cuando tiene
valor falso, en cuyo caso se imprime el mensaje como error.

Las pruebas se agrupan en funciones de cero argumentos que regresan
un booleano, si alguna de las pruebas falla esta función debe
regresar falso, si todas pasan debe regresar verdadero.

Dentro de estas funciones, utiliza una etiqueta fail para
identificar el código que libera recursos (como la memoria) cuando
una prueba falla.
*/
#define run_test(test)                             \
    do {                                           \
        fprintf(stderr, "* Testing " #test "..."); \
        bool ok = test();                          \
        if (!ok)                                   \
            return -1;                             \
        fprintf(stderr, "ok\n");                   \
    } while (0)

#define check(expr, message)                                                  \
    if (!(expr)) {                                                            \
        fprintf(stderr, "\nError (%s:%d) " message "\n", __FILE__, __LINE__); \
        goto fail;                                                            \
    }

int it_sums(void) {
    int n = 10;
    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        nums[i] = i + 1;

    int res = sum(nums, n);
    check((res == 55), "Expected sum of 1..10 to be 55.");
    return 1;
fail:
    printf("Got %d\n", res);
    return 0;
}

int it_rsums(void) {
    int n = 10;
    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        nums[i] = i + 1;

    check((rsum(nums, n) == 55), "Expected sum of 1..10 to be 55.");
    return 1;
fail:
    return 0;
}

int it_creates_vector(void) {
    int n = 3;
    int *vect = random_vector(n);
    if (vect != NULL)
        free(vect);
    return 1;
}

int it_bruteforces(void) {
    int degree = 100;
    int *coeffs = random_vector(degree + 1);
    double x = rand();
    double value = polyeval_bruteforce_v1(x, coeffs, degree);
    if (value == 0.0)
        return 0;
    if (coeffs != NULL)
        free(coeffs);
    return 1;
}

int it_bruteforces_better(void) {
    int degree = 10000;
    int *coeffs = random_vector(degree + 1);
    double x = irand();
    double result_1 = polyeval_bruteforce_v1(x, coeffs, degree);
    double result_2 = polyeval_bruteforce_v2(x, coeffs, degree);

    double delta = fabs(result_1 - result_2);
    double epsilon = 0.001;

    check((delta < epsilon),
          "Expected both bruteforce methods to return the same result.");

    if (coeffs != NULL)
        free(coeffs);
    return 1;
fail:
    if (coeffs != NULL)
        free(coeffs);
    return 0;
}

int it_horners(void) {
    int degree = 1000;
    int *coeffs = random_vector(degree + 1);
    double x = irand();

    double result_1 = polyeval_bruteforce_v2(x, coeffs, degree);
    double result_2 = polyeval_horner(x, coeffs, degree);

    double delta = fabs(result_1 - result_2);
    double epsilon = 0.001;
    check((delta < epsilon),
          "Expected horner's method to evaluate like bruteforce.");
    if (coeffs != NULL)
        free(coeffs);
    return 1;
fail:
    if (coeffs != NULL)
        free(coeffs);
    return 0;
}

int it_recurs_fib(void) {
    unsigned int N = 10;
    unsigned int fib = recursive_fibonacci(N);
    check((recursive_fibonacci(3) == 2), "Esperaba que fib(3)=2");
    check((fib == 55), "Esperaba que fib(10)=55.");
    return 1;
fail:
    printf("Got %d instead.\n", fib);
    return 0;
}

int it_iters_fib(void) {
    unsigned int N = 10;
    unsigned int fib = iterative_fibonacci(N);
    check((iterative_fibonacci(3) == 2), "Esperaba que fib(3)=2");
    check((fib == 55), "Esperaba que fib(10)=55.");
    return 1;
fail:
    printf("Got %d instead.\n", fib);
    return 0;
}

int it_memos_fib(void) {
    unsigned int N = 10;
    unsigned int fib = recursive_memoized_fibonacci(N);
    check((recursive_memoized_fibonacci(3) == 2), "Esperaba que fib(3)=2");
    check((fib == 55), "Esperaba que fib(10)=55.");
    return 1;
fail:
    printf("Got %d instead.\n", fib);
    return 0;
}

int it_creates_matrix(void) {
    int n = 3;
    int *mat = random_square_matrix(n);
    check((mat != NULL), "Expected a valid matrix.");
    if (mat != NULL)
        free_matrix(mat);
    return 1;

fail:
    if (mat != NULL)
        free_matrix(mat);
    return 0;
}

// i dont want to check if it is a valid algorithm

int it_transposes(void) {
    int n = 3;
    int *mat = random_square_matrix(n);
    int *mat_t = transpose(mat, n);
    check((mat_t != NULL), "Expected a valid matrix.");

    if (mat != NULL)
        free_matrix(mat);
    if (mat_t != NULL)
        free_matrix(mat_t);
    return 1;

fail:
    if (mat != NULL)
        free_matrix(mat);
    if (mat_t != NULL)
        free_matrix(mat_t);
    return 0;
}

int it_mults(void) {
    int n = 3;
    int *mat = random_square_matrix(n);
    int *mat2 = mult(mat, mat, n);
    check((mat2 != NULL), "Expected a valid matrix.");

    if (mat != NULL)
        free_matrix(mat);
    if (mat2 != NULL)
        free_matrix(mat2);
    return 1;

fail:
    if (mat != NULL)
        free_matrix(mat);
    if (mat2 != NULL)
        free_matrix(mat2);
    return 0;
}

int it_permutes(void) {
    int n = 3;
    int *vect = random_vecc(n);
    perm(vect, 0, n);

    if (vect != NULL)
        free(vect);
    return 1;
}

int main(void) {
    printf("\nTesting sums...\n");
    run_test(it_sums);
    run_test(it_rsums);
    printf("\nTesting polynomial evaluation...\n");
    run_test(it_creates_vector);
    run_test(it_bruteforces);
    run_test(it_bruteforces_better);
    run_test(it_horners);
    printf("\nTesting recursive methods\n");
    run_test(it_recurs_fib);
    run_test(it_iters_fib);
    run_test(it_memos_fib);
    printf("\nTesting matrix algorithms\n");
    run_test(it_creates_matrix);
    run_test(it_transposes);
    run_test(it_mults);
    printf("\nTesting permutation algorithms\n");
    run_test(it_permutes);
    printf("\nAll tests passed!\n");
    return 0;
}
