#include "sorting_methods.h"

void printList(int* lst, size_t n) {
    if (lst == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < n - 1; i++) printf("%d, ", *(lst + i));
    printf("%d]\n", *(lst + n - 1));
}

int* randint_list(int n, int lower, int upper) {
    if (n <= 0) return NULL;

    int* lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        *(lst + i) = (rand() % (upper + 1 - lower)) + lower;
    }
    return lst;
}

int* selection_sort(int* lst, size_t n, void (*f)()) {
    int* new_lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < (int)n; i++) {
        *(lst + i) = i;
    }

    f(lst, n);

    return new_lst;
}