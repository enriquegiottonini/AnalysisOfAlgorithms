#include <stdbool.h>

#include "sorting_methods.h"

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

#define check(expr, message)                             \
    if (!(expr)) {                                       \
        fprintf(stderr, "\nError (%s:%d) " message "\n", \
                __FILE__, __LINE__);                     \
        goto fail;                                       \
    }

// Auxiliary functions
bool leq(int x, int y) {
    return (x <= y);
}

bool geq(int x, int y) {
    return (x >= y);
}

int it_selection_sort() {
    size_t n = 20;
    int* lst = randint_list(n, -100, 100);
    int* ordered = selection_sort(lst, n, leq);
    check(is_ordered(ordered, n, leq), "Esperaba que se hubiera ordenado según la función leq");

    free(lst);
    if (ordered != NULL) free(ordered);
    return 1;

fail:
    free(lst);
    if (ordered != NULL) free(ordered);
    return 0;
}

int it_insertion_sort() {
    size_t n = 30;
    int* lst = randint_list(n, -100, 100);
    int* ordered = insertion_sort(lst, n, geq);

    check(is_ordered(ordered, n, geq), "Esperaba que se hubiera ordenado según la función geq");

    free(lst);
    if (ordered != NULL) free(ordered);
    return 1;

fail:
    free(lst);
    if (ordered != NULL) free(ordered);
    return 0;
}

int it_merges_same_size(void) {
    // Lists with the same size
    size_t n1 = 100;
    int* x1 = randint_list(n1, -100, 100);
    int* y1 = randint_list(n1, -50, 50);
    int* x1s = insertion_sort(x1, n1, leq);
    int* y1s = insertion_sort(y1, n1, leq);
    int* merged = merge(x1s, n1, y1s, n1, leq);

    check(is_ordered(merged, 2 * n1, leq), "Esperaba que los hubiera unido ordenadamente.");

    free(x1);
    free(y1);
    free(x1s);
    free(y1s);
    free(merged);
    return 1;
fail:
    free(x1);
    free(y1);
    free(x1s);
    free(y1s);
    free(merged);
    return 0;
}

int it_merges_different_size(void) {
    // Lists with different size
    size_t n1 = 101;
    size_t n2 = 50;
    int* x1 = randint_list(n1, -100, 100);
    int* y1 = randint_list(n2, -1000, 1000);
    int* x1s = insertion_sort(x1, n1, geq);
    int* y1s = insertion_sort(y1, n2, geq);
    int* merged = merge(x1s, n1, y1s, n2, geq);

    check(is_ordered(merged, n1 + n2, geq), "Esperaba que los hubiera unido ordenadamente.");

    free(x1);
    free(y1);
    free(x1s);
    free(y1s);
    free(merged);
    return 1;
fail:

    free(x1);
    free(y1);
    free(x1s);
    free(y1s);
    free(merged);
    return 0;
}

int it_merges_sort(void) {
    size_t n = 100;
    int* lst = randint_list(n, -100, 100);
    int* ordered = merge_sort(lst, n, geq);

    check(is_ordered(ordered, n, geq), "Esperaba que se hubiera ordenado según la función geq");

    free(lst);
    if (ordered != NULL) free(ordered);
    return 1;

fail:
    free(lst);
    if (ordered != NULL) free(ordered);
    return 0;
}

int it_swaps(void) {
    int x = 10;
    int y = 20;
    swap(&x, &y);

    check((x == 20) && (y == 10), "Esperaba que los valores hayan sido intercambiados.");
    return 1;

fail:
    return 0;
}

int it_copy_a_list(void) {
    size_t n = 100;
    int* x = randint_list(n, 0, 100);
    int* y = copy_list(x, n);
    for (int i = 0; i < (int)n; i++) {
        check(*(x + i) == *(y + i), "Esperaba que los valores en la posición i fueran iguales.")
    }
    if (x != NULL) free(x);
    if (y != NULL) free(y);
    return 1;

fail:
    if (x != NULL) free(x);
    if (y != NULL) free(y);
    return 0;
}

int it_checks_if_ordered(void) {
    int x[3] = {1, 2, 3};
    check(is_ordered(x, 3, leq), "Esperaba que checara que si está ordenada.");
    check(!(is_ordered(x, 3, geq)), "Esperaba que checara que no está ordenada.");
    return 1;

fail:
    return 0;
}

int it_creates_randint_list(void) {
    int* invalid = randint_list(-10, 1, 100);
    int* invalid2 = randint_list(0, 1, 100);
    int* lst = NULL;
    check((invalid == NULL) && (invalid2 == NULL), "Expected a NULL pointer in both invalid cases.");

    srand(time(NULL));
    int n = 5;
    int lower = 0;
    int upper = 5;
    lst = randint_list(n, lower, upper);

    for (int i = 0; i < n; i++) {
        int l_i = *(lst + 1);
        check((l_i >= lower) && (l_i <= upper), "Esperaba que estuviera dentro del rango [lower, upper]");
    }
    if (lst != NULL) free(lst);
    return 1;

fail:
    if (lst != NULL) free(lst);
    return 0;
}

int main(void) {
    run_test(it_creates_randint_list);
    run_test(it_checks_if_ordered);
    run_test(it_copy_a_list);
    run_test(it_swaps);
    run_test(it_selection_sort);
    run_test(it_insertion_sort);
    run_test(it_merges_same_size);
    run_test(it_merges_different_size);
    run_test(it_merges_sort);
    return 0;
}